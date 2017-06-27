/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 13:45:10 by gderenzi          #+#    #+#             */
/*   Updated: 2017/06/26 16:33:09 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	int				i;
	int				dest;
	unsigned int	new_color;

	new_color = mlx_get_color_value(mlx->ptr, color);
	dest = y * mlx->screen.s_line + x * mlx->screen.bits;
	i = 0;
	while (i < mlx->screen.bits)
	{
		if (mlx->screen.endian == 0)
			mlx->screen.data[dest + i] = new_color >> (i << 3) & 0xFF;
		else
			mlx->screen.data[dest + i] = new_color
				>> (mlx->screen.bits - ((i + 1) << 3)) & 0xFF;
		i++;
	}
}

void			draw_texture(t_mlx *mlx, t_img *img, t_point p, t_point w)
{
	int		i;
	int		src;
	int		dest;
	int		curr;

	src = w.y * img->s_line + w.x * img->bits;
	dest = p.y * mlx->screen.s_line + p.x * mlx->screen.bits;
	i = 0;
	while (i < img->bits)
	{
		if (mlx->k >= 1.0)
		{
			curr = img->data[src + i];
			curr += (curr < 0 ? 0xFF : 0);
			curr *= (1.0 / mlx->k);
			curr = (curr > 0xFF ? 0xFF : curr);
			curr = (curr < 0 ? 0 : curr);
			curr = (curr > 127 ? curr - 256 : curr);
			mlx->screen.data[dest + i] = curr;
		}
		else
			mlx->screen.data[dest + i] = img->data[src + i];
		i++;
	}
}

unsigned int	dark_color(unsigned int color, int y)
{
	int		i;
	double	k;
	int		n_color[3];

	k = 1.0 - (WIN_H - y) / (WIN_H / 2.0);
	k = k / 3.0;
	i = 0;
	while (i < 3)
	{
		n_color[i] = (color >> ((2 - i) << 3)) & 0xFF;
		n_color[i] = n_color[i] * k;
		n_color[i] = (n_color[i] > 0xFF ? 0xFF : n_color[i]);
		n_color[i] = (n_color[i] < 0 ? 0 : n_color[i]);
		i++;
	}
	return ((n_color[0] << 16) + (n_color[1] << 8) + n_color[2]);
}

void			draw_fill(t_mlx *mlx, int x, int wall_size, double deci)
{
	t_point	pos;
	t_point	wall;
	double	min_w;
	double	max_w;

	pos.x = x;
	pos.y = 0;
	min_w = WIN_H / 2.0 - wall_size;
	max_w = WIN_H / 2.0 + wall_size;
	while (pos.y < WIN_H)
	{
		wall.x = deci * mlx->curr_w.x;
		wall.y = ((double)(pos.y - min_w) / (max_w - min_w)) * mlx->curr_w.y;
		if (pos.y < min_w)
			draw_pixel(mlx, pos.x, pos.y, dark_color(0xFFFFFF, pos.y));
		else if (pos.y < max_w)
			draw_text(mlx, &mlx->curr_w, pos, wall);
		else
			draw_pixel(mlx, pos.x, pos.y, dark_color(0xFFFFFF, pos.y));
		(pos.y)++;
	}
}
