/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:56:28 by gderenzi          #+#    #+#             */
/*   Updated: 2017/06/26 16:05:17 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_hook_press(int keycode, t_mlx *mlx)
{
	if (keycode == QUIT)
		exit(1);
	if (keycode == MOVE_UP)
		mlx->event[0] = 1;
	if (keycode == MOVE_DOWN)
		mlx->event[1] = 1;
	if (keycode == MOVE_LEFT)
		mlx->event[2] = 1;
	if (keycode == MOVE_RIGHT)
		mlx->event[3] = 1;
	if (keycode == ROTATE_LEFT)
		mlx->event[4] = 1;
	if (keycode == ROTATE_RIGHT)
		mlx->event[5] = 1;
	return (0);
}

int		key_hook_release(int keycode, t_mlx *mlx)
{
	if (keycode == MOVE_UP)
		mlx->event[0] = 0;
	if (keycode == MOVE_DOWN)
		mlx->event[1] = 0;
	if (keycode == MOVE_LEFT)
		mlx->event[2] = 0;
	if (keycode == MOVE_RIGHT)
		mlx->event[3] = 0;
	if (keycode == ROTATE_LEFT)
		mlx->event[4] = 0;
	if (keycode == ROTATE_RIGHT)
		mlx->event[5] = 0;
	return (0);
}

int		loop_hook(t_mlx *mlx)
{
	int		flag;

	flag = 0;
	if (mlx->event[0] && (flag = 1))
		move(mlx, 1);
	if (mlx->event[1] && (flag = 1))
		move(mlx, -1);
	if (mlx->event[4] && (flag = 1))
		mlx->angle += (mlx->angle + 0.1 > 2 * M_PI ? -2 * M_PI + 0.1 : 0.1);
	if (mlx->event[5] && (flag = 1))
		mlx->angle += (mlx->angle - 0.1 < -2 * M_PI ? 2 * M_PI - 0.1 : -0.1);
	if (!flag)
		return (0);
	draw_wolf3d(mlx);
	draw_reload(mlx);
	return (0);
}
