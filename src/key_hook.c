/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:56:28 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/22 00:08:19 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_hook_press(int keycode, t_mlx *mlx)
{
	if (keycode == QUIT)
		quit(mlx);
	if (keycode == MOVE_UP)
		mlx->p.event[0] = 1;
	else if (keycode == MOVE_DOWN)
		mlx->p.event[0] = -1;
	if (keycode == MOVE_LEFT)
		mlx->p.event[1] = -1;
	else if (keycode == MOVE_RIGHT)
		mlx->p.event[1] = 1;
	if (keycode == LOOK_LEFT)
		mlx->p.event[2] = -1;
	else if (keycode == LOOK_RIGHT)
		mlx->p.event[2] = 1;
	if (keycode == LOOK_UP)
		mlx->p.event[3] = 1;
	else if (keycode == LOOK_DOWN)
		mlx->p.event[3] = -1;
	if (keycode == JUMP && mlx->p.event[4] == 0)
		mlx->p.event[4] = 1;
	if (keycode == CROUCH || keycode == ALT_CROUCH)
		mlx->p.event[5] = 1;
	if (keycode == K_SHOOT && mlx->p.event[6] == 0)
		mlx->p.event[6] = 1;
	return (1);
}

int		key_hook_release(int keycode, t_mlx *mlx)
{
	if (keycode == MOVE_UP || keycode == MOVE_DOWN)
		mlx->p.event[0] = 0;
	if (keycode == MOVE_LEFT || keycode == MOVE_RIGHT)
		mlx->p.event[1] = 0;
	if (keycode == LOOK_LEFT || keycode == LOOK_RIGHT)
		mlx->p.event[2] = 0;
	if (keycode == LOOK_UP || keycode == LOOK_DOWN)
		mlx->p.event[3] = 0;
	if (keycode == CROUCH || keycode == ALT_CROUCH)
		mlx->p.event[5] = 0;
	return (1);
}

int		mouse(int x, int y, t_mlx *mlx)
{
	if (x != mlx->mousex)
	{
		mlx->p.a += (mlx->mousex - x) * 0.2 * R_SPEED;
		mlx->mousex = x;
	}
	if (y != mlx->mousey)
	{
		mlx->scr.center += (mlx->mousey - y) * R_SPEED;
		mlx->mousey = y;
	}
	mlx->p.a += (mlx->p.a > 360 ? -360 : 0);
	mlx->p.a += (mlx->p.a < 0 ? 360 : 0);
	return (1);
}

int		shoot(int button, int x, int y, t_mlx *mlx)
{
	x = y;
	y = x;
	if (button == M_SHOOT && mlx->p.event[6] == 0)
		mlx->p.event[6] = 1;
	return (1);
}

int		draw_reload(t_mlx *mlx)
{
	mlx->ntouch = -1;
	mlx->delay = (mlx->delay == 0 ? 1 : 0);
	mlx->delay2 = !(mlx->delay + mlx->delay2 == 1 ? 1 : 0);
	draw_wolf3d(mlx);
	mlx->distt = 75 + cos(mlx->p.bob) * 10;
	weapon_handling(mlx);
	path_handling(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->scr.ptr, 0, 0);
	movement(mlx);
	gravity(mlx);
	return (1);
}
