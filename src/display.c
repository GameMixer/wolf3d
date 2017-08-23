/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 13:34:24 by gderenzi          #+#    #+#             */
/*   Updated: 2017/07/25 15:49:44 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	find_limit(t_mlx *mlx, int x, int n)
{
	t_vlst	*list;
	double	rdist;
	int		i;

	mlx->bot = -1;
	mlx->top = -1;
	if (x >= 0 && x < mlx->scr.w)
	{
		rdist = mlx->slst.s[n].dist * ((cos((mlx->p.a -
							mlx->slst.s[n].a) / 180 * M_PI)));
		i = mlx->line[x].iter;
		list = mlx->line[x].list;
		while (i-- > 0 && list->next && rdist > list->next->vector.dist)
			list = list->next;
	}
	if (x >= 0 && x < mlx->scr.w && list && i > 0)
	{
		mlx->bot = list->hf;
		mlx->top = list->hc;
	}
}

void	display_sprite(t_mlx *mlx, int n, double pas)
{
	double	x;
	double	y;

	mlx->slst.s[n].uvx = 0;
	x = mlx->slst.s[n].bx;
	mlx->distt = mlx->slst.s[n].dist;
	while (x < mlx->slst.s[n].tx)
	{
		y = mlx->slst.s[n].ty;
		mlx->slst.s[n].uvy = 0;
		find_limit(mlx, x, n);
		while (y < mlx->slst.s[n].by)
		{
			if (y >= mlx->top && y <= mlx->bot && x >= 0 && x < mlx->scr.w
					&& y >= 0 && y < mlx->scr.h)
				render_points(mlx, x, y, n);
			mlx->slst.s[n].uvy += pas;
			y++;
		}
		mlx->slst.s[n].uvx += pas;
		x++;
	}
}

double	get_sprite_coord(t_mlx *mlx, int n)
{
	double	ytmp;
	double	xtmp;
	double	pas;

	mlx->slst.s[n].a = -(atan2(mlx->slst.s[n].y - mlx->p.y,
				mlx->slst.s[n].x - mlx->p.x) * (180 / M_PI));
	mlx->slst.s[n].a += (mlx->slst.s[n].a < 0 ? 360 : 0);
	ytmp = mlx->p.a + (FOV / 2) - mlx->slst.s[n].a;
	if (mlx->slst.s[n].a > 270 && mlx->p.a < 90)
		ytmp += 360;
	if (mlx->p.a > 270 && mlx->slst.s[n].a < 90)
		ytmp -= 360;
	xtmp = ytmp * (mlx->scr.w / (double)FOV);
	mlx->slst.s[n].by = (mlx->scr.center + ((mlx->p.h * mlx->scr.dist) /
				mlx->slst.s[n].dist) / 2);
	mlx->slst.s[n].ty = mlx->slst.s[n].by - (((mlx->p.h * mlx->scr.dist) /
				mlx->slst.s[n].dist) * ((mlx->slst.s[n].z + 64) /
					mlx->p.h) / 2);
	mlx->slst.s[n].by = mlx->slst.s[n].by - (((mlx->p.h * mlx->scr.dist) /
				mlx->slst.s[n].dist) * (mlx->slst.s[n].z / mlx->p.h) / 2);
	mlx->slst.s[n].bx = xtmp - ((mlx->slst.s[n].by - mlx->slst.s[n].ty) / 2);
	mlx->slst.s[n].tx = xtmp + ((mlx->slst.s[n].by - mlx->slst.s[n].ty) / 2);
	pas = (double)BLOCK / (mlx->slst.s[n].by - mlx->slst.s[n].ty);
	return (pas);
}
