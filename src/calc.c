/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 12:49:52 by gderenzi          #+#    #+#             */
/*   Updated: 2017/06/23 13:45:01 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	calc_kx(t_mlx *mlx, t_prec vector)
{
	int		x;
	int		y;
	int		fix;
	double	k;
	double	kx;

	k = 9000;
	x = 0;
	while (x < MAP_W)
	{
		fix = (vector.x < 0) * -1;
		kx = (x - mlx->x) / vector.x;
		y = mlx->y + kx * vector.y;
		if (kx >= 0 && y >= 0 && y < MAP_H &&
				mlx->map[x + fix][y] != '0' && kx < k)
			k = kx;
		x++;
	}
	return (k);
}

double	calc_ky(t_mlx *mlx, t_prec vector)
{
	int		x;
	int		y;
	int		fix;
	double	k;
	double	ky;

	k = 9000;
	y = 0;
	while (y < MAP_H)
	{
		fix = (vector.y < 0) * -1;
		ky = (y - mlx->y) / vector.y;
		x = mlx->x + ky * vector.x;
		if (ky >= 0 && x >= 0 && x < MAP_W &&
				mlx->map[x][y + fix] != '0' && ky < k)
			k = ky;
		y++;
	}
	return (k);
}

void	calc_side_and_texture(t_mlx *mlx, int x, t_prec vector)
{
	int		xflag;
	t_prec	decimal;
	t_prec	k;
	t_point	fix;

	mlx->k = calc_kx(mlx, vector);
	if (mlx->k > (k.y = calc_ky(mlx, vector)))
	{
		mlx->k = k.y;
		xflag = 0;
	}
	else
		xflag = 1;
	fix.x = (xflag == 1 && vector.x < 0) * -1;
	fix.y = (xflag == 0 && vector.y < 0) * -1;
	decimal.x = mlx->x + mlx->k * vector.x - (int)(mlx->x + mlx->k * vector.x);
	decimal.y = mlx->y + mlx->k * vector.y - (int)(mlx->y + mlx->k * vector.y);
	mlx->curr_w = mlx->wall[mlx->map[(int)(mlx->x + mlx->k * vector.x + fix.x)]
		[(int)(mlx->y + mlx->k * vector.y + fix.y)] - '1'];
	if (xflag)
		draw_fill(mlx, x, WIN_H / (2 * mlx->k), decimal.y);
	else
		draw_fill(mlx, x, WIN_H / (2 * mlx->k), decimal.x);
}

void	draw_wolf3d(t_mlx *mlx)
{
	int		x;
	double	x1;
	double	y1;
	t_prec	vector;

	x = 0;
	while (x < WIN_W)
	{
		y1 = 1.0 * (WIN_W / 2 - x) / WIN_W;
		x1 = 0.5 * cos(mlx->angle) - y1 * sin(mlx->angle) + mlx->x;
		y1 = 0.5 * sin(mlx->angle) + y1 * cos(mlx->angle) + mlx->y;
		vector.x = x1 - mlx->x;
		vector.y = y1 - mlx->y;
		calc_side_and_texture(mlx, x, vector);
		x++;
	}
}
