/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:11:31 by gderenzi          #+#    #+#             */
/*   Updated: 2017/06/26 18:03:43 by gderenzi         ###   ########.fr       */
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
# define MOVE_LEFT = KEY_A
# define MOVE_RIGHT = KEY_D
# define TURN_LEFT = KEY_LEFT
# define TURN_RIGHT = KEY_RIGHT

# define WALLS 8
# define EVENTS 6

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_precision
{
	double			x;
	double			y;
}					t_prec;

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
	int				event[EVENTS];
	char			map[MAP_W][MAP_H];
	t_img			screen;
	t_img			sky;
	t_img			wall[WALLS];
	t_img			curr_w;
	double			angle;
	double			x;
	double			y;
	double			k;
}					t_mlx;

/*
**	Initializes the variables and loads in the wall textures
**		load.c
*/
void				load_all(t_mlx *mlx);
void				load_wall(t_mlx *mlx);
void				load_img(t_mlx *mlx, t_img *img, char *path);

/*
**	Get the map that is already hard coded in.
**		map.c
*/
void				get_map(char mlxmap[MAP_W][MAP_H]);
char				map_part1(int x, int y);
char				map_part2(int x, int y);
char				map_part3(int x, int y);

/*
**	Calculates what is needed to be drawn, and what doesn't
**		calc.c
*/
void				draw_wolf3d(t_mlx *mlx);
void				calc_side_and_textures(t_mlx *mlx, int x, t_prec vector);
double				calc_kx(t_mlx *mlx, t_prec vector);
double				calc_ky(t_mlx *mlx, t_prec vector);

/*
**	Draws everything, shading it as well
**		draw.c
*/
void				draw_pixel(t_mlx *mlx, int x, int y, unsigned int color);
void				draw_fill(t_mlx *mlx, int x, int wall_size, double deci);
void				draw_texture(t_mlx *mlx, t_img *img, t_point p, t_point w);
unsigned int		dark_color(unsigned int color, int y);

/*
**	Key events go through here
**		key_hook.c
*/
int					loop_hook(t_mlx *mlx);
int					key_hook_press(t_mlx *mlx);
int					key_hook_release(t_mlx *mlx);

/*
**	Different tools are stored here when I have no idea where else to put them
**		util.c
*/
int					draw_reload(t_mlx *mlx);
void				move(t_mlx *mlx, int vdir, int hdir);
double				pythag(double a, double b);

/*
**	Error messages...even though there is just one...Shut up.
**		error.c
*/
int					error_mlx(void);

# endif
