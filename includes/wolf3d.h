/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 15:11:31 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/22 00:10:14 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "get_next_line.h"
# include <mlx.h>
# include <math.h>
# include "colors.h"
# include "keys.h"
# include <stdio.h>
# include <time.h>

# define WIN_W 1280
# define WIN_H 720

# define MAP_W 60
# define MAP_H 64

# define FOV 60
# define BLOCK 64
# define SCALE 2

# define QUIT			KEY_ESC
# define MOVE_UP		KEY_W
# define MOVE_DOWN		KEY_S
# define MOVE_LEFT		KEY_A
# define MOVE_RIGHT		KEY_D
# define LOOK_LEFT		KEY_LEFT
# define LOOK_RIGHT		KEY_RIGHT
# define LOOK_UP		KEY_UP
# define LOOK_DOWN		KEY_DOWN
# define JUMP			KEY_SPACE
# define CROUCH			KEY_L_CTRL
# define ALT_CROUCH		KEY_C
# define M_SHOOT		MOUSE_CLICK_L
# define K_SHOOT		KEY_RETURN

# define HT_SPEED 3
# define VT_SPEED 12
# define M_SPEED 8
# define R_SPEED 1
# define GRAVITY 12

# define TEXTURES 127
# define EVENTS 7
# define SOLDIER_INDEX 112
# define WEAPON_INDEX 122

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

typedef struct		s_vector
{
	double			x;
	double			y;
	int				uvx;
	int				uvy;
	double			dist;
}					t_vector;

typedef struct		s_vlst
{
	t_vector		vector;
	char			side;
	int				floorsv;
	int				floorev;
	int				floorbot;
	int				floortop;
	int				ceilsv;
	int				ceilev;
	int				ceilbot;
	int				ceiltop;
	int				wfloorbot;
	int				wfloorsv;
	int				wfloortop;
	int				wfloorev;
	int				wceilbot;
	int				wceilsv;
	int				wceiltop;
	int				wceilev;
	int				wallc;
	int				wallf;
	int				hc;
	int				hf;
	struct s_vlst	*next;
}					t_vlst;

typedef struct		s_line
{
	t_vlst			*list;
	double			angle;
	int				iter;
}					t_line;

typedef struct		s_player
{
	double			x;
	double			y;
	double			z;
	double			h;
	double			a;
	double			bob;
	int				event[EVENTS];
	int				jump;
	int				weapon;
	double			life;
}					t_player;

typedef struct		s_map
{
	char			*name;
	int				w;
	int				h;
	int				**floor;
	int				**ceiling;
	int				**texture;
	t_player		firstpos;
}					t_map;

typedef struct		s_precomp
{
	double			a;
	double			rad_a;
	double			tan_a;
	int				mapw;
	int				maph;
	double			playx;
	double			playy;
	double			playa;
	double			distort;
}					t_precomp;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			z;
	double			dist;
	int				size;
	int				texture;
	int				enemy;
	int				state;
	int				attack;
	double			a;
	int				bx;
	int				tx;
	int				by;
	int				ty;
	double			uvx;
	double			uvy;
	double			life;
}					t_sprite;

typedef struct		s_spr_lst
{
	int				n;
	t_sprite		*s;
}					t_spr_lst;

typedef struct		s_img
{
	void			*ptr;
	unsigned char	*data;
	int				w;
	int				h;
	int				center;
	int				dist;
	double			angle_w;
	int				bits;
	int				size;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	char			**data;
	char			**file;
	t_player		p;
	t_map			map;
	t_img			scr;
	t_img			sky;
	t_img			*tex;
	t_img			curr_w;
	t_precomp		precomp;
	t_line			*line;
	t_spr_lst		slst;
	int				hc;
	int				hf;
	double			x;
	double			y;
	int				curr_t;
	double			dist;
	double			distt;
	int				vx;
	int				vy;
	int				pixel;
	double			ax;
	double			ay;
	double			dist_f;
	double			dist_c;
	int				ntouch;
	int				delay;
	int				delay2;
	int				floorx;
	int				floory;
	int				color;
	int				wall_f;
	int				wall_c;
	int				bot_f;
	int				bot_c;
	int				bot;
	int				top;
	int				mousex;
	int				mousey;
}					t_mlx;

/*
**	Loads in the wall textures
**		load.c
*/
void				load_all(t_mlx *mlx, char *file);
void				load_texture(t_mlx *mlx);
int					load_map(t_mlx *mlx, char *file);
void				load_path(t_mlx *mlx);

/*
**	Initializes some variables for later use, like vectors
**		init.c
*/
void				init_value(t_mlx *mlx, double dist);
void				init_vector_hori(t_precomp *prec, t_vector *h);
void				init_vector_vert(t_precomp *prec, t_vector *v);

/*
**	Get the map that is already hard coded in.
**		map.c
*/
void				map_set(t_mlx *mlx, int fd, int nbl, int j);
char				*map_buff(int *nbl, int fd);
void				map_scan(t_mlx *mlx, int len);
int					**map_get(t_mlx *mlx, int *i);
void				get_p(t_mlx *mlx, int *i);

/*
**	Casts rays, obviously, that will be used in calculating what to draw
**		ray_cast.c
*/
void				draw_wolf3d(t_mlx *mlx);
void				cast_ray(t_precomp *prec, t_map *map, t_vlst **list);
void				cast_hori(t_precomp *prec, t_vector *h);
void				cast_vert(t_precomp *prec, t_vector *v);

/*
**	Calculates what is needed to be drawn, and what doesn't
**		calc.c
*/
void				line_cleaner(t_mlx *mlx, t_vlst *vlst, int num);
int					calc_floor(t_vlst **list, t_mlx *mlx, int wallf, int bot);
int					calc_ceil(t_vlst **list, t_mlx *mlx, int wallc, int bot);
int					calc_wfloor(t_vlst **list, t_mlx *mlx,
						int *wallf, int *fbot);
int					calc_wceil(t_vlst **list, t_mlx *mlx,
						int *wallc, int *cbot);

/*
**	Draws everything, shading it as well
**		draw.c
*/
void				draw_line(t_mlx *mlx, t_vlst *list, int num);
void				draw_floor(t_mlx *mlx, t_vlst *list, int num);
void				draw_ceil(t_mlx *mlx, t_vlst *list, int num);
void				draw_wallf(t_mlx *mlx, t_vlst *list, int num);
void				draw_wallc(t_mlx *mlx, t_vlst *list, int num);

/*
**	This is where things will actually be drawn, but I didn't want to make
**	another file named draw2.c. I try to avoid using numbers in files
**	as much as I can
**		render.c
*/
void				put_pixel(t_mlx *mlx, int x, int y);
void				render_points(t_mlx *mlx, int x, int y, int n);
void				render_pointfc(t_mlx *mlx, int num, int t);
void				render_pointwv(t_mlx *mlx, int num, int t);
void				render_pointwh(t_mlx *mlx, int num, int t);

/*
**	Handles what to do with the sprites in the game.
**		sprite.c
*/
void				get_sprite_data(t_mlx *mlx, char **data, int n);
void				get_sprite_list(t_mlx *mlx, int *i);
void				sprite_sort(t_mlx *mlx);
void				sprite_calc(t_mlx *mlx);
void				sprite_display(t_mlx *mlx);

/*
**	Another case of me not wanting to make a file with 2 in it. This
**	finishes up displaying the sprites calculated beforehand
**		display.c
*/
void				display_sprite(t_mlx *mlx, int n, double pas);
double				get_sprite_coord(t_mlx *mlx, int n);
void				find_limit(t_mlx *mlx, int x, int n);

/*
**	Determines where the enemy can or cant shoot and walk at
**		path.c
*/
void				path_handling(t_mlx *mlx);
void				sprite_shoot(t_mlx *mlx, int move, int i);
int					path_finding(t_mlx *mlx, int i);
int					path_correct(t_mlx *mlx, int i, int type);

/*
**	What kind of first person shooter game would it be without a gun?
**		weapon.c
*/
void				weapon_handling(t_mlx *mlx);
void				weapon_display(t_mlx *mlx, int state);

/*
**	Key events go through here
**		key_hook.c
*/
int					draw_reload(t_mlx *mlx);
int					key_hook_press(int keycode, t_mlx *mlx);
int					key_hook_release(int keycode, t_mlx *mlx);
int					mouse(int x, int y, t_mlx *mlx);
int					shoot(int button, int x, int y, t_mlx *mlx);

/*
**	Functions for walking around, even though they are all basically the same
**	just with sin instead of cos and adding instead of subtracting
**	and vice versa
**		movement.c
*/
void				move_front(t_mlx *mlx);
void				move_back(t_mlx *mlx);
void				move_left(t_mlx *mlx);
void				move_right(t_mlx *mlx);
void				movement(t_mlx *mlx);

/*
**	Where all the vector functions are kept, which are used for ray casting
**		vector.c
*/
t_vlst				*vect_new(t_vector *content, char side);
void				vect_init(t_vlst **list);
void				vect_addsort(t_vlst **vlst, t_vector *content, char side);
void				vect_clear(t_vlst **vlst);

/*
**	Different tools are stored here when I have no idea where else to put them
**		util.c
*/
void				pre_compute(t_mlx *mlx, double ray);
int					jump(t_mlx *mlx);
void				gravity(t_mlx *mlx);
int					quit(t_mlx *mlx);
int					linelen(char *buff, int k);

/*
**	Error messages...the most basic file out of ALL of these.
**		error.c
*/
int					error_mlx(void);
void				error_arg(void);
void				error_texture(void);
void				error_malloc(void);
void				error_map(int reason);

#endif
