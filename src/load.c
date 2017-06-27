/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 12:05:26 by gderenzi          #+#    #+#             */
/*   Updated: 2017/06/26 16:15:42 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_img(t_mlx *mlx, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(mlx->ptr, path, &img->x, &img->y);
	img->data = mlx_get_data_addr(img->ptr, &img->bits,
			&img->s_line, &img->endian);
	img->bits = img->bits >> 3;
}

void	load_wall(t_mlx *mlx)
{
	int		i;
	char	*path[WALLS] = {"imgs/blue_wall.xpm", "imgs/brick_wall.xpm",
	"imgs/desert_wall.xpm", "imgs/eagle_wall.xpm", "imgs/smooth_wall.xpm",
	"imgs/stone_wall.xpm", "imgs/tile_wall.xpm", "imgs/wood_wall.xpm"};

	i = 0;
	while (i < WALLS)
	{
		load_img(mlx, &mlx->wall[i], path[i]);
		i++;
	}
}

void	load_all(t_mlx *mlx)
{
	int		i;
	//t_img	load;

	mlx->x = 30.5;
	mlx->y = 8.5;
	mlx->angle = 4.7;
	i = 0;
	while (i < EVENTS)
	{
		mlx->event[i] = 0;
		i++;
	}
	mlx->screen.ptr = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->screen.data = mlx_get_data_addr(mlx->screen.ptr, &mlx->screen.bits,
			&mlx->screen.s_line, &mlx->screen.endian);
	load_wall(mlx);
	get_map(mlx->map);
}
