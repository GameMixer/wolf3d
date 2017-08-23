/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:12:41 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/22 00:01:43 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	controls(void)
{
	ft_putendl("\033[31;1m======== Wolf3d Controls ========\033[0m");
	ft_putendl("\033[31;1mW, A, S, D -          Walk around\033[0m");
	ft_putendl("\033[31;1mArrow Keys/Mouse -    Look around\033[0m");
	ft_putendl("\033[31;1mSpace Bar -                  Jump\033[0m");
	ft_putendl("\033[31;1mC -                        Crouch\033[0m");
	ft_putendl("\033[31;1mReturn/Left Mouse -         Shoot\033[0m");
	ft_putendl("\033[31;1mESC -                        Quit\033[0m");
	ft_putendl("\033[31;1m=================================\033[0m");
}

int			main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
		error_arg();
	load_all(&mlx, argv[1]);
	controls();
	mlx_hook(mlx.win, 2, 1, &key_hook_press, &mlx);
	mlx_hook(mlx.win, 3, 2, &key_hook_release, &mlx);
	mlx_hook(mlx.win, 6, 64, &mouse, &mlx);
	mlx_hook(mlx.win, 4, 4, &shoot, &mlx);
	mlx_hook(mlx.win, 17, (1L << 17), quit, &mlx);
	mlx_loop_hook(mlx.ptr, &draw_reload, &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
