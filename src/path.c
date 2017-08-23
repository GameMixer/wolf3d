/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 13:15:03 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/01 11:42:08 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	sprite_shoot(t_mlx *mlx, int move, int i)
{
	if (move == 1 && mlx->slst.s[i].attack > 0 && mlx->slst.s[i].state == 2)
	{
		mlx->slst.s[i].state += (((int)mlx->p.bob % 2) == 1 ? mlx->delay : 0);
		if (mlx->slst.s[i].state == 3)
			mlx->p.life -= (mlx->delay2 == 0 ? 10.0 : 0);
	}
	if (move == 1 && mlx->slst.s[i].attack == 0 && mlx->delay == 0)
	{
		mlx->slst.s[i].attack = 1;
		mlx->slst.s[i].state = 2;
	}
	if (mlx->slst.s[i].attack > 0)
		mlx->slst.s[i].attack += (mlx->slst.s[i].attack == 10 ? -10 : 1);
}

int		path_correct(t_mlx *mlx, int i, int type)
{
	int		v;

	if (type == 1)
	{
		v = (mlx->slst.s[i].x > mlx->p.x ? -3 : 3);
		if (mlx->map.floor[(int)mlx->slst.s[i].y / BLOCK]
				[(int)(mlx->slst.s[i].x + v) / BLOCK] ==
				mlx->map.floor[(int)mlx->slst.s[i].y / BLOCK]
				[(int)mlx->slst.s[i].x / BLOCK])
		{
			mlx->slst.s[i].x += v;
			return (0);
		}
	}
	v = (mlx->slst.s[i].y > mlx->p.y ? -3 : 3);
	if (mlx->map.floor[(int)(mlx->slst.s[i].y + v) / BLOCK]
			[(int)mlx->slst.s[i].x / BLOCK] ==
			mlx->map.floor[(int)mlx->slst.s[i].y / BLOCK]
			[(int)mlx->slst.s[i].x / BLOCK])
	{
		mlx->slst.s[i].y += v;
		return (0);
	}
	return (1);
}

int		path_finding(t_mlx *mlx, int i)
{
	int		x;
	int		y;

	x = fabs(mlx->p.x - mlx->slst.s[i].x);
	y = fabs(mlx->p.y - mlx->slst.s[i].y);
	if (mlx->slst.s[i].texture == SOLDIER_INDEX && mlx->slst.s[i].dist > 32)
	{
		if (y < x)
			return (path_correct(mlx, i, 1));
		else
			return (path_correct(mlx, i, 2));
	}
	return (1);
}

void	path_handling(t_mlx *mlx)
{
	int		i;

	i = 0;
	while (i < mlx->slst.n)
	{
		if (mlx->slst.s[i].life <= 0)
		{
			mlx->slst.s[i].state += (mlx->slst.s[i].state == 9
					? 0 : mlx->delay);
			mlx->slst.s[i].size = 8;
		}
		else if (mlx->slst.s[i].attack == 0)
			mlx->slst.s[i].state = 0;
		if (mlx->slst.s[i].enemy == 1 && mlx->slst.s[i].dist < 200
				&& mlx->slst.s[i].life > 0)
			sprite_shoot(mlx, path_finding(mlx, i), i);
		i++;
	}
	if (mlx->ntouch != -1 && mlx->slst.s[mlx->ntouch].life >= 0
			&& mlx->p.weapon != 0 && mlx->slst.s[mlx->ntouch].enemy == 1)
	{
		mlx->slst.s[mlx->ntouch].life -= (mlx->p.weapon == 1 ? 25 : 0);
		mlx->slst.s[mlx->ntouch].state = 4;
	}
}
