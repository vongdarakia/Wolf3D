/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:24:28 by avongdar          #+#    #+#             */
/*   Updated: 2017/05/04 19:24:29 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define MAP_WIDTH 64
# define MAP_HEIGHT 64
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define SIDE_Y 1
# define SIDE_X 0
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define ABS(x) ((x) < 0 ? -(x) : (x))
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define NUM_KEYS 512

# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "mlx.h"
# include "get_next_line.h"

typedef struct	s_pos_i
{
	int x;
	int y;
}				t_pos_i;

typedef struct	s_pos_f
{
	double x;
	double y;
}				t_pos_f;

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct	s_env
{
	char			*img_ptr;
	void			*img;
	void			*mlx;
	void			*win;
	int				bpp;
	int				line_size;
	int				endian;

	int				m_height;
	int				m_width;
	int				tex_height;
	int				tex_width;

	double			move_spd;
	double			rot_spd;
	double			camera_x;

	t_point			pos;
	t_pos_f			ray_pos;
	t_pos_f			ray_dir;
	t_pos_f			plane;
	t_pos_f			dir;

	t_pos_f			dlt_dist;
	t_pos_f			side_dist;
	t_pos_i			step;
	t_pos_i			map;
	int				line_height;
	int				side;
	int				hit;

	t_pos_i			tex;
	int				tex_num;
	int				draw_start;
	int				draw_end;
	double			x2;
	double			y2;
	int				x;
	int				y;
	int				d;
	double			wall_dist;
	double			wall_x;
	double			dir_len;
	int				color;

	double			prev_time;
	double			frame_time;
	clock_t			end_time;

	unsigned int	**buffer;
	int				**texture;
	int				**w_map;
	int				keys[NUM_KEYS];

	t_pos_i			prev;
}				t_env;

t_point			point(int x, int y);
t_pos_i			pos_i(int x, int y);
t_pos_f			pos_f(double x, double y);

void			read_map(t_env *e, char *filename);

void			draw_point_to_img(t_env *e, int x, int y, int color);
void			draw_line(t_env *e, t_point p0, t_point p1, int color);
void			draw_buffer(t_env *e);
void			draw_rays(t_env *e);

void			cast_ray(t_env *e);
int				get_wall_height(t_env *e);

int				loop_hook(t_env *e);
int				close_hook(t_env *e);
int				key_pressed(int keycode, t_env *e);
int				key_released(int keycode, t_env *e);

void			rotate(t_env *e, double rot_spd);
void			move_straight(t_env *e, double speed);

int				is_str_numeric(char *str);
int				get_width(char **words);

void			free_map(char **map);
void			free_mapn(char **map, int num);
#endif
