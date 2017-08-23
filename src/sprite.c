/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 12:31:51 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/21 23:21:02 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_sprite_data(t_mlx *mlx, char **data, int n)
{
	mlx->slst.s[n].x = (double)ft_atoi(data[0]) * BLOCK + 32;
	mlx->slst.s[n].y = (double)ft_atoi(data[1]) * BLOCK + 32;
	mlx->slst.s[n].z = (double)ft_atoi(data[2]);
	mlx->slst.s[n].texture = ft_atoi(data[3]);
	mlx->slst.s[n].size = ft_atoi(data[4]);
	mlx->slst.s[n].enemy = ft_atoi(data[5]);
	mlx->slst.s[n].state = 0;
	mlx->slst.s[n].life = 100.0;
	mlx->slst.s[n].attack = 0;
}

void	get_sprite_list(t_mlx *mlx, int *i)
{
	char	**data_line;
	int		x;

	x = 0;
	*i = *i + 1;
	if (!mlx->data[*i])
		error_map(5);
	data_line = ft_strsplit(mlx->data[*i], ' ');
	mlx->slst.n = ft_atoi(data_line[0]);
	mlx->slst.s = (t_sprite *)malloc(sizeof(t_sprite) * mlx->slst.n);
	ft_strtab_free(data_line);
	while (x < mlx->slst.n)
	{
		*i = *i + 1;
		data_line = ft_strsplit(mlx->data[*i], ' ');
		get_sprite_data(mlx, data_line, x);
		ft_strtab_free(data_line);
		x++;
	}
}

void	sprite_sort(t_mlx *mlx)
{
	int			x;
	int			y;
	int			done;
	t_sprite	tmp;

	x = 0;
	done = 1;
	while (x < mlx->slst.n && done)
	{
		y = 1;
		done = 0;
		while (y < (mlx->slst.n - x))
		{
			if (mlx->slst.s[y - 1].dist < mlx->slst.s[y].dist)
			{
				tmp = mlx->slst.s[y - 1];
				mlx->slst.s[y - 1] = mlx->slst.s[y];
				mlx->slst.s[y] = tmp;
				done = 1;
			}
			y++;
		}
		x++;
	}
}

void	sprite_calc(t_mlx *mlx)
{
	int		n;
	double	pas;

	n = 0;
	while (n < mlx->slst.n)
	{
		pas = get_sprite_coord(mlx, n);
		if ((mlx->slst.s[n].bx >= 0 && mlx->slst.s[n].bx < mlx->scr.w) ||
				(mlx->slst.s[n].tx >= 0 && mlx->slst.s[n].tx < mlx->scr.w) ||
				(mlx->slst.s[n].bx < 0 && mlx->slst.s[n].tx > mlx->scr.w))
			display_sprite(mlx, n, pas);
		n++;
	}
}

void	sprite_display(t_mlx *mlx)
{
	int		x;

	x = 0;
	while (x < mlx->slst.n)
	{
		mlx->slst.s[x].dist = ((sqrt(pow((mlx->p.x - mlx->slst.s[x].x), 2.0) +
						pow((mlx->p.y - mlx->slst.s[x].y), 2.0))) /
				((double)BLOCK / 64)) / SCALE;
		if (mlx->slst.s[x].dist < 16)
			mlx->slst.s[x].dist = 16;
		x++;
	}
	sprite_sort(mlx);
	sprite_calc(mlx);
}
