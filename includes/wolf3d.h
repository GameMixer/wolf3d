/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:11:31 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 16:08:44 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include "colors.h"
# include "keys.h"

# define WIN_W 1920
# define WIN_H 1080

# define MAP_W 60
# define MAP_H 64

# define QUIT = KEY_ESC
# define MOVE_UP = KEY_W
# define MOVE_DOWN = KEY_S
# define TURN_LEFT = KEY_A
# define TURN_RIGHT = KEY_D

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_img
{
	void			*ptr;
	char			*data;
	int				x;
	int				y;
	int				bits;
	int				s_line;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;



# endif
