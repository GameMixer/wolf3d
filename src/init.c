/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 12:56:22 by gderenzi          #+#    #+#             */
/*   Updated: 2017/07/13 16:39:00 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_vector_hori(t_precomp *prec, t_vector *h)
{
	if (prec->a >= 180 && prec->a < 360)
	{
		h->y = floor(prec->playy / BLOCK) * BLOCK + BLOCK;
		h->uvy = 64;
	}
	else
	{
		h->y = floor(prec->playy / BLOCK) * BLOCK - 0.001;
		h->uvy = 0;
	}
	h->x = prec->playx + (prec->playy - h->y) / prec->tan_a;
	h->uvx = (int)h->x % 64;
	h->dist = ((sqrt(pow((prec->playx - h->x), 2.0) +
					pow((prec->playy - h->y), 2.0))) * prec->distort) /
		((double)BLOCK / 64);
}

void	init_vector_vert(t_precomp *prec, t_vector *v)
{
	if (prec->a >= 90 && prec->a < 270)
	{
		v->x = floor(prec->playx / BLOCK) * BLOCK - 0.001;
		v->uvx = 0;
	}
	else
	{
		v->x = floor(prec->playx / BLOCK) * BLOCK + BLOCK;
		v->uvx = 64;
	}
	v->y = prec->playy + (prec->playx - v->x) * prec->tan_a;
	v->uvy = (int)v->y % 64;
	v->dist = ((sqrt(pow((prec->playx - v->x), 2.0) +
					pow((prec->playy - v->y), 2.0))) * prec->distort) /
		((double)BLOCK / 64);
}

void	init_value(t_mlx *mlx, double dist)
{
	mlx->ax = mlx->p.x;
	mlx->ay = mlx->p.y;
	mlx->vx = 0;
	mlx->vy = 0;
	mlx->dist_c = dist;
	mlx->dist_f = dist;
}
