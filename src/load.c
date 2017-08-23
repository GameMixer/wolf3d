/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 12:05:26 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/22 00:07:16 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_path(t_mlx *mlx)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("src/textures/sprite_list", O_RDONLY);
	if (fd < 0)
		error_texture();
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		mlx->file[i] = line;
		i++;
	}
}

void	load_texture(t_mlx *mlx)
{
	int		i;

	mlx->tex = (t_img *)malloc(sizeof(t_img) * TEXTURES);
	mlx->file = (char **)malloc(sizeof(char *) * TEXTURES);
	load_path(mlx);
	i = 0;
	while (i < TEXTURES)
	{
		mlx->tex[i].ptr = mlx_xpm_file_to_image(mlx->ptr, mlx->file[i],
				&mlx->tex[i].w, &mlx->tex[i].h);
		if (mlx->tex[i].ptr == NULL)
			error_texture();
		mlx->tex[i].data = (unsigned char *)mlx_get_data_addr(mlx->tex[i].ptr,
				&mlx->tex[i].bits, &mlx->tex[i].size, &mlx->tex[i].endian);
		i++;
	}
}

int		load_map(t_mlx *mlx, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	map_set(mlx, fd, 0, 0);
	return (1);
}

void	load_all(t_mlx *mlx, char *file)
{
	int		i;

	if (!load_map(mlx, file))
		error_map(0);
	if (!(mlx->ptr = mlx_init()))
		error_mlx();
	i = 0;
	mlx->scr.w = WIN_W;
	mlx->scr.h = WIN_H;
	mlx->win = mlx_new_window(mlx->ptr, mlx->scr.w, mlx->scr.h, mlx->map.name);
	mlx->scr.angle_w = (double)FOV / mlx->scr.w;
	mlx->scr.ptr = mlx_new_image(mlx->ptr, mlx->scr.w, mlx->scr.h);
	mlx->scr.data = (unsigned char *)mlx_get_data_addr(mlx->scr.ptr,
			&mlx->scr.bits, &mlx->scr.size, &mlx->scr.endian);
	mlx->scr.dist = (mlx->scr.w / 2) / 0.57735026;
	mlx->scr.center = mlx->scr.h / 2;
	mlx->line = (t_line *)malloc(sizeof(t_line) * mlx->scr.w);
	mlx->mousex = mlx->scr.w / 2;
	mlx->mousey = mlx->scr.h / 2;
	load_texture(mlx);
}
