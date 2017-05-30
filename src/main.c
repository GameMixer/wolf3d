/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:12:41 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 15:58:41 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(void)
{
	t_mlx	mlx;

	if (!(mlx.ptr = mlx_init()))
		return (error_mlx());
	mlx.win = mlx_new_window(mlx.ptr, WIN_W, WIN_H, "Wolf3D");
	init_all(&mlx);
	draw_wolf3d(&mlx);
	mlx_expose_hook(mlx.win, , &mlx);
	mlx_hook(mlx.win, 2, 1, key_hook, &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
