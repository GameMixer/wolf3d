/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 12:49:52 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 18:18:23 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	cast_hori(t_precomp *prec, t_vector *h)
{
	if (prec->a >= 180 && prec->a < 360)
	{
		h->y += BLOCK;
		h->x -= (BLOCK / prec->tan_a);
		h->uvy = 64;
	}
	else
	{
		h->y -= BLOCK;
		h->x += (BLOCK / prec->tan_a);
		h->uvy = 0;
	}
	h->uvx = (int)h->x % 64;
	h->dist = ((sqrt(pow((prec->playx - h->x), 2.0) +
					pow((prec->playy - h->y), 2.0))) * prec->distort) /
		((double)BLOCK / 64);
}

void	cast_vert(t_precomp *prec, t_vector *v)
{
	if (prec->a >= 90 && prec->a < 270)
	{
		v->x -= BLOCK;
		v->y += (BLOCK * prec->tan_a);
		v->uvx = 0;
	}
	else
	{
		v->x += BLOCK;
		v->y -= (BLOCK * prec->tan_a);
		v->uvx = 64;
	}
	v->uvy = (int)v->y % 64;
	v->dist = ((sqrt(pow((prec->playx - v->x), 2.0) +
					pow((prec->playy - v->y), 2.0))) * prec->distort) /
		((double)BLOCK / 64);
}

void	cast_ray(t_precomp *prec, t_map *map, t_vlst **list)
{
	t_vector	rh;
	t_vector	rv;

	init_vector_vert(prec, &rv);
	while ((rv.x >= 0 && rv.x < prec->mapw && rv.y >= 0 && rv.y < prec->maph)
			&& map->floor[(int)(rv.y / BLOCK)][(int)(rv.x / BLOCK)]
			< map->ceiling[(int)(rv.y / BLOCK)][(int)(rv.x / BLOCK)])
	{
		vect_addsort(*&list, &rv, 'v');
		cast_vert(prec, &rv);
	}
	init_vector_hori(prec, &rh);
	while ((rh.x >= 0 && rh.x < prec->mapw && rh.y >= 0 && rh.y < prec->maph)
			&& map->floor[(int)(rh.y / BLOCK)][(int)(rh.x / BLOCK)]
			< map->ceiling[(int)(rh.y / BLOCK)][(int)(rh.x / BLOCK)])
	{
		vect_addsort(*&list, &rh, 'h');
		cast_hori(prec, &rh);
	}
	if (rh.dist > rv.dist && rv.x >= 0 && rv.x < prec->mapw &&
			rv.y >= 0 && rv.y < prec->maph)
		vect_addsort(*&list, &rv, 'v');
	else if (rh.dist < rv.dist && rh.x >= 0 && rh.x < prec->mapw &&
			rh.y >= 0 && rh.y < prec->maph)
		vect_addsort(*&list, &rh, 'h');
}

void	draw_wolf3d(t_mlx *mlx)
{
	int		scanline;
	double	ray_ang;

	scanline = 0;
	ray_ang = mlx->p.a + (FOV / 2);
	while (scanline < mlx->scr.w)
	{
		pre_compute(mlx, ray_ang);
		mlx->line[scanline].list = NULL;
		cast_ray(&mlx->precomp, &mlx->map, &mlx->line[scanline].list);
		line_cleaner(mlx, mlx->line[scanline].list, scanline);
		ray_ang -= mlx->scr.angle_w;
		scanline++;
	}
	sprite_display(mlx);
	scanline = 0;
	while (scanline < mlx->scr.w)
	{
		vect_clear(&mlx->line[scanline].list);
		scanline++;
	}
}
