/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 14:25:38 by gderenzi          #+#    #+#             */
/*   Updated: 2017/07/31 16:22:39 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	weapon_display(t_mlx *mlx, int state)
{
	int		pos;
	double	pas;
	double	x;
	double	y;
	double	bob;

	mlx->y = mlx->scr.h;
	pas = (128.0 / mlx->scr.w) * 3;
	y = 127;
	bob = ((mlx->p.event[0] || mlx->p.event[1]) ? cos(mlx->p.bob) : 0);
	while ((y -= pas) >= 0 && (mlx->y -= 1) > 0)
	{
		x = 0;
		mlx->x = mlx->scr.w / 2 - 1;
		while ((x += pas) < 128 && (mlx->x += 1) < mlx->scr.w)
		{
			pos = ((int)x * mlx->tex[state].bits / 8) +
				((int)y * mlx->tex[state].size);
			mlx->color = mlx->tex[state].data[pos] +
				mlx->tex[state].data[pos + 1] * 256 +
				mlx->tex[state].data[pos + 2] * 65536;
			if (mlx->color != 0x980088)
				put_pixel(mlx, mlx->x + bob * 25, mlx->y + fabs(bob * 75));
		}
	}
}

void	weapon_handling(t_mlx *mlx)
{
	if (mlx->p.event[6] == 1)
		mlx->p.weapon++;
	if (mlx->p.weapon > 4)
	{
		mlx->p.weapon = 0;
		mlx->p.event[6] = 0;
	}
	weapon_display(mlx, mlx->p.weapon + WEAPON_INDEX);
}
