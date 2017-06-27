/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:48:23 by gderenzi          #+#    #+#             */
/*   Updated: 2017/06/26 18:34:14 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move(t_mlx *mlx, int vdir, int hdir)
{
	double	x;
	double	y;

	if (vdir && hdir)
	{
		x = mlx->x + (vdir * hdir * cos(mlx->angle - ((M_PI / 4) * hdir)) * 0.15);
		y = mlx->y + (vdir * hdir * sin(mlx->angle - ((M_PI / 4) * hdir)) * 0.15);
	}
	else if (vdir && !hdir)
	{
		x = mlx->x + (vdir * cos(mlx->angle) * 0.15);
		y = mlx->y + (vdir * sin(mlx->angle) * 0.15);
	}
	else
	{
		x = mlx->x + (hdir * cos(mlx->angle - ((M_PI / 2) * hdir)) * 0.15);
		y = mlx->y + (hdir * sin(mlx->angle - ((M_PI / 2) * hdir)) * 0.15);
	}
	if (mlx->map[(int)x][(int)y] != '0')
	{
		if (mlx->map[(int)mlx->x][(int)y] == '0')
			mlx->y = y;
		else if (mlx->map[(int)x][(int)mlx->y] == '0')
			mlx->x = x;
	}
	else
	{
		mlx->x = x;
		mlx->y = y;
	}
}

double	pythag(double a, double b)
{
	double	c;

	c = (a * a) + (b * b);
	c = sqrt(c);
	return (c);
}

int		draw_reload(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->screen.ptr, 0, 0);
	return (0);
}
