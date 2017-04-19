#ifndef WOLF3D_H
# define WOLF3D_H
# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480
# define ABS(x) ((x) < 0 ? -(x) : (x))
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define LEFT 123
# define DOWN 125
# define RIGHT 124
# define ESC 53
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_pos_i
{
	int x;
	int y;
}				t_pos_i;

typedef struct s_pos_f
{
	double x;
	double y;
}				t_pos_f;

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct s_env
{
	t_point pos;
	t_point dir;
	t_point plane_l;
	t_point plane_r;
	t_point plane;

	char *img_ptr;
	void *img;
	void *mlx;
	void *win;
	int bpp;
	int line_size;
	int endian;
	int				w_height;
	int				w_width;
	int				m_height;
	int				m_width;
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
	t_pos_i 	map;
	//length of ray from current position to next x or y-side
	t_pos_f side_dist;
	//length of ray from one x or y-side to next x or y-side
	t_pos_i step;
	int			line_height;
	int			side;
	int			hit;
	t_pos_f		dlt_dist;
	unsigned int **buffer;
	int **texture;
	struct timeval startTime;
	struct timeval endTime;
	int px;
	int py;
	int dir_x;
	int dir_y;
	int color;
	int **w_map;
}			t_env;



void	read_map(t_env *e, char *filename);
void	draw_point_to_img(t_env *e, int x, int y, int color);
void	draw_line_xslope(t_env *e, t_point p0, t_point p1, int color);
void	draw_line_yslope(t_env *e, t_point p0, t_point p1, int color);
void	draw_line(t_env *e, t_point p0, t_point p1, int color);
void	draw_buffer(t_env *e);
void	draw_rays(t_env *e);
void	cast_ray(t_env *e);
int		get_wall_height(t_env *e);

void	draw_minimap(t_env *e);
#endif
