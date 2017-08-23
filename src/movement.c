/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 12:20:04 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/01 11:35:30 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_front(t_mlx *mlx)
{
	double	x;
	double	y;
	double	dist;

	x = mlx->p.x + M_SPEED * cos(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((mlx->p.y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(mlx->p.y / BLOCK)][(int)(x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(mlx->p.y / BLOCK)]
			[(int)(x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.x += M_SPEED * cos(mlx->p.a / 180 * M_PI);
	y = mlx->p.y - M_SPEED * sin(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((mlx->p.x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(y / BLOCK)][(int)(mlx->p.x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(y / BLOCK)]
			[(int)(mlx->p.x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.y -= M_SPEED * sin(mlx->p.a / 180 * M_PI);
}

void	move_back(t_mlx *mlx)
{
	double	x;
	double	y;
	double	dist;

	x = mlx->p.x - M_SPEED * cos(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((mlx->p.y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(mlx->p.y / BLOCK)][(int)(x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(mlx->p.y / BLOCK)]
			[(int)(x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.x -= M_SPEED * cos(mlx->p.a / 180 * M_PI);
	y = mlx->p.y + M_SPEED * sin(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((mlx->p.x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(y / BLOCK)][(int)(mlx->p.x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(y / BLOCK)]
			[(int)(mlx->p.x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.y += M_SPEED * sin(mlx->p.a / 180 * M_PI);
}

void	move_right(t_mlx *mlx)
{
	double	x;
	double	y;
	double	dist;

	x = mlx->p.x + M_SPEED * sin(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((mlx->p.y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(mlx->p.y / BLOCK)][(int)(x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(mlx->p.y / BLOCK)]
			[(int)(x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.x += M_SPEED * sin(mlx->p.a / 180 * M_PI);
	y = mlx->p.y + M_SPEED * cos(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((mlx->p.x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(y / BLOCK)][(int)(mlx->p.x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(y / BLOCK)]
			[(int)(mlx->p.x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.y += M_SPEED * cos(mlx->p.a / 180 * M_PI);
}

void	move_left(t_mlx *mlx)
{
	double	x;
	double	y;
	double	dist;

	x = mlx->p.x - M_SPEED * sin(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((mlx->p.y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(mlx->p.y / BLOCK)][(int)(x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(mlx->p.y / BLOCK)]
			[(int)(x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.x -= M_SPEED * sin(mlx->p.a / 180 * M_PI);
	y = mlx->p.y - M_SPEED * cos(mlx->p.a / 180 * M_PI);
	dist = ((sqrt(pow((mlx->p.x - mlx->slst.s[mlx->slst.n - 1].x), 2.0) +
					pow((y - mlx->slst.s[mlx->slst.n - 1].y), 2.0))))
		/ ((double)BLOCK / 64);
	if (mlx->map.floor[(int)(y / BLOCK)][(int)(mlx->p.x / BLOCK)]
			<= mlx->p.z + 8 && mlx->map.ceiling[(int)(y / BLOCK)]
			[(int)(mlx->p.x / BLOCK)] > mlx->p.h && dist
			> mlx->slst.s[mlx->slst.n - 1].size)
		mlx->p.y -= M_SPEED * cos(mlx->p.a / 180 * M_PI);
}

void	movement(t_mlx *mlx)
{
	if (mlx->p.event[0] == -1)
		move_back(mlx);
	else if (mlx->p.event[0] == 1)
		move_front(mlx);
	if (mlx->p.event[1] == -1)
		move_left(mlx);
	else if (mlx->p.event[1] == 1)
		move_right(mlx);
	if (mlx->p.event[2] == -1)
		mlx->p.a += (mlx->p.a + HT_SPEED > 360 ? -360 + HT_SPEED : HT_SPEED);
	else if (mlx->p.event[2] == 1)
		mlx->p.a += (mlx->p.a - HT_SPEED < 0 ? 360 - HT_SPEED : -HT_SPEED);
	if (mlx->p.event[3] == 1)
		mlx->scr.center += (mlx->scr.center + VT_SPEED < (mlx->scr.h * 2)
				? VT_SPEED : 0);
	else if (mlx->p.event[3] == -1)
		mlx->scr.center += (mlx->scr.center - VT_SPEED > 0 ? -VT_SPEED : 0);
	if (mlx->p.event[4] == 1)
		mlx->p.event[4] = jump(mlx);
}
