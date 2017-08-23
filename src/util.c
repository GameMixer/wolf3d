/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:48:23 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/22 00:09:40 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		quit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(1);
	return (0);
}

int		jump(t_mlx *mlx)
{
	if (mlx->p.jump < 15 && mlx->p.h <= mlx->map.ceiling[(int)mlx->p.y / BLOCK]
			[(int)mlx->p.x / BLOCK])
		mlx->p.z += GRAVITY + (8 - (mlx->p.jump += 1));
	if (mlx->p.z == mlx->map.floor[(int)(mlx->p.y / BLOCK)]
			[(int)(mlx->p.x / BLOCK)])
	{
		mlx->p.jump = 0;
		return (0);
	}
	return (1);
}

void	gravity(t_mlx *mlx)
{
	if (mlx->map.floor[(int)floor(mlx->p.y / BLOCK)]
			[(int)floor(mlx->p.x / BLOCK)] < mlx->p.z)
		mlx->p.z -= GRAVITY;
	if (mlx->map.floor[(int)floor(mlx->p.y / BLOCK)]
			[(int)floor(mlx->p.x / BLOCK)] > mlx->p.z)
		mlx->p.z = mlx->map.floor[(int)floor(mlx->p.y / BLOCK)]
			[(int)floor(mlx->p.x / BLOCK)];
	mlx->p.h = mlx->p.z + 31 + (cos(mlx->p.bob += 0.15) * 2) +
		(mlx->p.event[5] == 1 ? -16 : 0);
}

void	pre_compute(t_mlx *mlx, double ray)
{
	mlx->precomp.a = ray;
	mlx->precomp.a += (mlx->precomp.a < 0 ? 360 : 0);
	mlx->precomp.a += (mlx->precomp.a > 360 ? -360 : 0);
	mlx->precomp.rad_a = ray / 180.0 * M_PI;
	mlx->precomp.tan_a = tan(mlx->precomp.rad_a);
	mlx->precomp.mapw = mlx->map.w * BLOCK;
	mlx->precomp.maph = mlx->map.h * BLOCK;
	mlx->precomp.playx = mlx->p.x;
	mlx->precomp.playy = mlx->p.y;
	mlx->precomp.playa = mlx->p.a;
	mlx->precomp.distort = (cos((mlx->precomp.playa - mlx->precomp.a)
				/ 180 * M_PI)) / SCALE;
}

int		linelen(char *buff, int k)
{
	int		len;

	len = 0;
	while (buff[k] != '\n' && buff[k] != '\0')
	{
		k++;
		len++;
	}
	return (++len);
}
