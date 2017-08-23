/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:10:49 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/21 23:23:57 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	put_pixel(t_mlx *mlx, int x, int y)
{
	int		pos;
	double	div;

	if (x >= 0 && x < mlx->scr.w && y >= 0 && y < mlx->scr.h)
	{
		pos = (x * mlx->scr.bits / 8) + (y * mlx->scr.size);
		div = 1 + (mlx->distt / 100.0);
		mlx->scr.data[pos] = (mlx->color % 256) / div;
		mlx->scr.data[pos + 1] = ((mlx->color >> 8) % 256) / div;
		mlx->scr.data[pos + 2] = ((mlx->color >> 16) % 256) / div;
	}
}

void	render_pointwv(t_mlx *mlx, int num, int t)
{
	int		p;

	p = ((mlx->vy) * mlx->tex[t + 1].bits / 8) +
		((int)mlx->x * mlx->tex[t + 1].size);
	mlx->color = mlx->tex[t].data[p] +
		mlx->tex[t].data[p + 1] * 256 +
		mlx->tex[t].data[p + 2] * 65536;
	put_pixel(mlx, num, mlx->pixel);
}

void	render_pointwh(t_mlx *mlx, int num, int t)
{
	int		p;

	p = ((mlx->vx) * mlx->tex[t + 1].bits / 8) +
		((int)mlx->x * mlx->tex[t + 1].size);
	mlx->color = mlx->tex[t].data[p] +
		mlx->tex[t].data[p + 1] * 256 +
		mlx->tex[t].data[p + 2] * 65536;
	put_pixel(mlx, num, mlx->pixel);
}

void	render_pointfc(t_mlx *mlx, int num, int t)
{
	int		p;

	p = ((int)mlx->x * mlx->tex[t].bits / 8) + ((int)mlx->y * mlx->tex[t].size);
	mlx->color = mlx->tex[t].data[p] +
		mlx->tex[t].data[p + 1] * 256 +
		mlx->tex[t].data[p + 2] * 65536;
	put_pixel(mlx, num, mlx->pixel);
}

void	render_points(t_mlx *mlx, int x, int y, int n)
{
	int		p;

	p = ((((int)mlx->slst.s[n].uvx) * mlx->tex[mlx->slst.s[n].texture +
				mlx->slst.s[n].state].bits) / 8) + (((int)mlx->slst.s[n].uvy) *
				mlx->tex[mlx->slst.s[n].texture + mlx->slst.s[n].state].size);
	mlx->color = mlx->tex[mlx->slst.s[n].texture
		+ mlx->slst.s[n].state].data[p]
		+ mlx->tex[mlx->slst.s[n].texture
		+ mlx->slst.s[n].state].data[p + 1] * 256
		+ mlx->tex[mlx->slst.s[n].texture
		+ mlx->slst.s[n].state].data[p + 2] * 65536;
	if (mlx->color != 0x980088)
	{
		put_pixel(mlx, x, y);
		if (x == mlx->scr.w / 2 && y == mlx->scr.h / 2)
			mlx->ntouch = n;
	}
}
