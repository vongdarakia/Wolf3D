#ifndef WOLF3D_H
# define WOLF3D_H
# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480
# define ABS(x) ((x) < 0 ? -(x) : (x))
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_pos_f
{
	double x;
	double y;
}				t_pos_f;

typedef struct s_env
{
	char *img_ptr;
	void *img;
	void *mlx;
	void *win;
	int bpp;
	int line_size;
	int endian;
	int				w_height;
	int				w_width;
	int				tex_height;
	int				tex_width;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
	double		cameraX;
	t_pos_f		ray_pos;
	t_pos_f		ray_dir;
	unsigned int **buffer;
	int **texture;
	struct timeval startTime;
	struct timeval endTime;
	int px;
	int py;
	int dir_x;
	int dir_y;
	int color;
}			t_env;

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

void	draw_point_to_img(t_env *e, int x, int y, int color);

void	draw_line_xslope(t_env *e, t_point p0, t_point p1, int color);

void	draw_line_yslope(t_env *e, t_point p0, t_point p1, int color);

void	draw_line(t_env *e, t_point p0, t_point p1, int color);

void	draw_buffer(t_env *e);

#endif
