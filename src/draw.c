/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 13:45:10 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 18:17:58 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_wallf(t_mlx *mlx, t_vlst *list, int num)
{
	double	pas;

	pas = ((double)BLOCK / ((list->wfloorbot + list->wfloorsv) -
				(list->wfloortop - list->wfloorev)));
	pas *= ((double)list->wallf / BLOCK);
	mlx->x = (list->wfloorsv * pas);
	mlx->curr_t = mlx->map.texture[(int)floor(list->vector.y / BLOCK)]
		[(int)floor(list->vector.x / BLOCK)] * 4 + 1;
	mlx->pixel = list->wfloorbot;
	while (mlx->pixel >= list->wfloortop)
	{
		mlx->x += (mlx->x > 64.0 ? -64.0 : 0);
		if (mlx->pixel < mlx->scr.h && mlx->pixel >= 0
				&& mlx->x >= 0 && mlx->x <= 64)
		{
			if (list->side == 'v')
				render_pointwv(mlx, num, mlx->curr_t + 1);
			else
				render_pointwh(mlx, num, mlx->curr_t);
		}
		mlx->x += pas;
		mlx->pixel -= 1;
	}
}

void	draw_wallc(t_mlx *mlx, t_vlst *list, int num)
{
	double	pas;

	pas = ((double)BLOCK / ((list->wceiltop + list->wceilev) -
				(list->wceilbot - list->wceilsv)));
	pas *= ((512.0 - (double)list->wallc) / BLOCK);
	mlx->x = 64 - (list->wceilsv * pas);
	mlx->curr_t = mlx->map.texture[(int)floor(list->vector.y / BLOCK)]
		[(int)floor(list->vector.x / BLOCK)] * 4 + 1;
	mlx->pixel = list->wceilbot;
	while (mlx->pixel <= list->wceiltop)
	{
		mlx->x += (mlx->x < 0 ? 64.0 : 0);
		if (mlx->pixel < mlx->scr.h && mlx->pixel >= 0
				&& mlx->x >= 0 && mlx->x <= 64)
		{
			if (list->side == 'v')
				render_pointwv(mlx, num, mlx->curr_t + 1);
			else
				render_pointwh(mlx, num, mlx->curr_t);
		}
		mlx->x -= pas;
		mlx->pixel += 1;
	}
}

void	draw_floor(t_mlx *mlx, t_vlst *list, int num)
{
	double	pasx;
	double	pasy;
	double	pas;
	double	pasdist;

	pas = (list->floorbot + list->floorsv) - (list->floortop - list->floorev);
	pasx = (-(mlx->x - list->vector.uvx)) / pas;
	pasy = (-(mlx->y - list->vector.uvy)) / pas;
	pasdist = (list->vector.dist - mlx->dist_f) / pas;
	mlx->x += (list->floorsv * pasx);
	mlx->y += (list->floorsv * pasy);
	mlx->curr_t = mlx->map.texture[(int)floor(mlx->ay / BLOCK)]
		[(int)floor(mlx->ax / BLOCK)] * 4;
	mlx->pixel = list->floorbot;
	mlx->distt = mlx->dist_f;
	while (mlx->pixel >= list->floortop)
	{
		if (mlx->pixel < mlx->scr.h && mlx->pixel >= 0 && mlx->x >= 0
				&& mlx->x <= 64 && mlx->y >= 0 && mlx->y <= 64)
			render_pointfc(mlx, num, mlx->curr_t);
		mlx->distt += pasdist;
		mlx->pixel -= 1;
		mlx->x += pasx;
		mlx->y += pasy;
	}
}

void	draw_ceil(t_mlx *mlx, t_vlst *list, int num)
{
	double	pasx;
	double	pasy;
	double	pas;
	double	pasdist;

	pas = (list->ceiltop + list->ceilev) - (list->ceilbot - list->ceilsv);
	pasx = (-(mlx->x - list->vector.uvx)) / pas;
	pasy = (-(mlx->y - list->vector.uvy)) / pas;
	pasdist = (list->vector.dist - mlx->dist_c) / pas;
	mlx->x += (list->ceilsv * pasx);
	mlx->y += (list->ceilsv * pasy);
	mlx->curr_t = mlx->map.texture[(int)floor(mlx->ay / BLOCK)]
		[(int)floor(mlx->ax / BLOCK)] * 4 + 3;
	mlx->pixel = list->ceilbot;
	mlx->distt = mlx->dist_c;
	while (mlx->pixel <= list->ceiltop)
	{
		if (mlx->pixel < mlx->scr.h && mlx->pixel >= 0 && mlx->x >= 0
				&& mlx->x <= 64 && mlx->y >= 0 && mlx->y <= 64)
			render_pointfc(mlx, num, mlx->curr_t);
		mlx->distt += pasdist;
		mlx->pixel += 1;
		mlx->x += pasx;
		mlx->y += pasy;
	}
}

void	draw_line(t_mlx *mlx, t_vlst *list, int num)
{
	int		n;

	init_value(mlx, list->vector.dist);
	n = mlx->line[num].iter;
	while (list && n-- > 0)
	{
		mlx->dist = list->vector.dist;
		mlx->x = mlx->vx;
		mlx->y = mlx->vy;
		draw_floor(mlx, list, num);
		mlx->x = mlx->vx;
		mlx->y = mlx->vy;
		draw_ceil(mlx, list, num);
		mlx->vx = (int)list->vector.x % 64;
		mlx->vy = (int)list->vector.y % 64;
		mlx->distt = list->vector.dist;
		draw_wallf(mlx, list, num);
		draw_wallc(mlx, list, num);
		mlx->ax = list->vector.x;
		mlx->ay = list->vector.y;
		mlx->dist_c = list->vector.dist;
		mlx->dist_f = list->vector.dist;
		list = list->next;
	}
}
