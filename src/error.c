/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:45:11 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/01 10:45:16 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		error_mlx(void)
{
	ft_putstr("wolf3d: error with mlx_init\n");
	return (1);
}

void	error_texture(void)
{
	ft_putstr("wolf3d: error with loading textures\n");
	exit(2);
}

void	error_malloc(void)
{
	ft_putstr("wolf3d: error with malloc\n");
	exit(3);
}

void	error_arg(void)
{
	ft_putstr("wolf3d: error with arguments\n");
	ft_putstr("\tusage: ./wolf3d <directory> <map>\n");
	exit(4);
}

void	error_map(int reason)
{
	ft_putstr("wolf3d: error with map. ");
	if (reason == 0)
		ft_putstr("File does not exist\n");
	else if (reason == 1)
		ft_putstr("There is nothing to read\n");
	else if (reason == 2)
		ft_putstr("There is no width and/or height for the map\n");
	else if (reason == 3)
		ft_putstr("The map is not valid\n");
	else if (reason == 4)
		ft_putstr("Player data not valid\n");
	else
		ft_putstr("The sprite list is not valid\n");
	exit(5);
}
