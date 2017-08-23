/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 11:27:53 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/21 23:28:30 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_p(t_mlx *mlx, int *i)
{
	char	**p_data;
	int		j;

	*i = *i + 1;
	if (!mlx->data[*i])
		error_map(4);
	p_data = ft_strsplit(mlx->data[*i], ' ');
	mlx->p.x = (ft_atoi(p_data[0]) * BLOCK) - (BLOCK / 2) + BLOCK;
	mlx->p.y = (ft_atoi(p_data[1]) * BLOCK) - (BLOCK / 2) + BLOCK;
	mlx->p.z = ft_atoi(p_data[2]);
	mlx->p.h = mlx->p.z + 32;
	mlx->p.a = ft_atoi(p_data[3]);
	mlx->p.bob = 0;
	mlx->p.jump = 1;
	j = -1;
	while (++j < EVENTS)
		mlx->p.event[j] = 0;
	ft_strtab_free(p_data);
	mlx->p.weapon = 0;
	mlx->p.life = 100.0;
}

int		**map_get(t_mlx *mlx, int *i)
{
	int		x;
	int		y;
	char	**array;
	int		**map;

	if (!mlx->map.w || !mlx->map.h)
		error_map(2);
	x = -1;
	*i = *i + 1;
	if (!(map = (int **)malloc(sizeof(int *) * mlx->map.h)))
		error_malloc();
	while (++x < mlx->map.h)
	{
		if (!mlx->data[*i + x])
			error_map(3);
		array = ft_strsplit(mlx->data[*i + x], ' ');
		if (!(map[x] = (int *)malloc(sizeof(int) * mlx->map.w)))
			error_malloc();
		y = -1;
		while (++y < mlx->map.w && array[y])
			map[x][y] = ft_atoi(array[y]);
		ft_strtab_free(array);
	}
	*i = *i + mlx->map.h - 1;
	return (map);
}

void	map_scan(t_mlx *mlx, int len)
{
	int	i;

	i = 0;
	while (mlx->data[i] && i < len)
	{
		if (ft_strstr(mlx->data[i], "MAP NAME :"))
			mlx->map.name = ft_strdup(mlx->data[i] + 11);
		else if (ft_strstr(mlx->data[i], "MAP WIDTH :"))
			mlx->map.w = ft_atoi((mlx->data[i] + 12));
		else if (ft_strstr(mlx->data[i], "MAP HEIGHT :"))
			mlx->map.h = ft_atoi((mlx->data[i] + 13));
		else if (ft_strstr(mlx->data[i], "HEIGHT MAP : FLOOR"))
			mlx->map.floor = map_get(mlx, &i);
		else if (ft_strstr(mlx->data[i], "HEIGHT MAP : CEILING"))
			mlx->map.ceiling = map_get(mlx, &i);
		else if (ft_strstr(mlx->data[i], "TEXTURE MAP :"))
			mlx->map.texture = map_get(mlx, &i);
		else if (ft_strstr(mlx->data[i], "PLAYER POSITION :"))
			get_p(mlx, &i);
		else if (ft_strstr(mlx->data[i], "SPRITE LIST :"))
			get_sprite_list(mlx, &i);
		i++;
	}
}

char	*map_buff(int *nbl, int fd)
{
	char	*buff;
	char	*line;

	buff = ft_strnew(1);
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
		buff = ft_strjoin_free(buff, ft_strjoin_free(line, "\n", 'L'), 'B');
	if (close(fd) == -1)
		error_map(6);
	return (buff);
}

void	map_set(t_mlx *mlx, int fd, int nbl, int j)
{
	char	*buff;
	int		i;
	int		k;

	k = 0;
	buff = map_buff(&nbl, fd);
	if (!buff)
		error_map(1);
	if (!(mlx->data = (char **)malloc(sizeof(char *) * (nbl + 1))))
		error_malloc();
	while (buff[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(mlx->data[j] = (char *)malloc(sizeof(char) * linelen(buff, k))))
			error_malloc();
		while (buff[k] != '\n' && buff[k] != '\0')
			mlx->data[j][i++] = buff[k++];
		mlx->data[j][i] = '\0';
		k++;
		j++;
	}
	free(buff);
	map_scan(mlx, nbl);
}
