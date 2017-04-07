#include "wolf3d.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_user_pos
{
	int x;
	int y;
	int dir_x;
	int dir_y;
}				t_user_pos;

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

int		is_wall(int x, int y)
{
	return worldMap[x][y] > 0;
}

t_pos_i *get_hor_wall(t_env *e, double deg)
{
	t_pos_i *wall_pos;
	t_pos_i a;
	t_pos_i ray;
	int ya;
	int xa;

	deg = deg < 30 ? 90 - (30 - deg) : 90 - (deg - 30);
	a.y = floor(e->py / 64.0) * 64 + (e->dir_y > 0 ? -1 : 64);
	a.x = e->px + (e->py - a.y) / atan(deg);

	ya = (e->dir_y > 0) ? -64 : 64;
	xa = fabs(64 / atan(deg));

	ray.x = (a.x + xa);
	ray.y = (a.y + ya);
	printf("xa: %d, ya: %d\n", xa, ya);
	printf("checking map[%d][%d] deg: %.2f\n\n", ray.x / 64, ray.y / 64, deg);
	while (!is_wall(ray.x / 64, ray.y / 64)) {
		ray.x += xa;
		ray.y += ya;
	}
	wall_pos = (t_pos_i*)malloc(sizeof(t_pos_i));
	wall_pos->x = ray.x / 64;
	wall_pos->y = ray.y / 64;
	return wall_pos;
}

t_pos_i *get_ver_wall(t_env *e, double deg)
{
	t_pos_i *wall_pos;
	t_pos_i a;
	t_pos_i ray;
	int ya;
	int xa;
	
	deg = deg < 30 ? 90 - (30 - deg) : 90 - (deg - 30);
	a.x = floor(e->px / 64) * 64 + (e->dir_x > 0 ? 64 : -1);
	a.y = e->py + (e->px - a.x) / atan(deg);
	xa = (e->dir_x > 0) ? -64 : 64;
	ya = 64 / atan(deg);
	ray.x = (a.x + xa);
	ray.y = (a.y + ya);

	while (!is_wall(ray.x / 64, ray.y / 64)) {
		ray.x += xa;
		ray.y += ya;
	}
	wall_pos = (t_pos_i*)malloc(sizeof(t_pos_i));
	wall_pos->x = ray.x / 64;
	wall_pos->y = ray.y / 64;
	return wall_pos;
}

double get_wall_dist() {

	return 0.0;
}

void set_color_based_on_pos(t_env *e, t_pos_i *pos)
{
	switch(worldMap[pos->x][pos->y])
	{
		case 1:  e->color = 0xFF0000;  break; //red
		case 2:  e->color = 0x00FF00;  break; //green
		case 3:  e->color = 0x0000FF;   break; //blue
		case 4:  e->color = 0xFFFFFF;  break; //white
		default: e->color = 0xFFFF00; break; //yellow
	}
}

double get_closest_dist(t_env *e, double beta, t_pos_i *w1, t_pos_i *w2) {
	double d1;
	double d2;
	// double beta;

	// beta = deg > 30 ? deg - 30 : 30 - deg;
	d1 = sqrt(pow(e->px - (w1)->x, 2) + pow(e->py - (w1)->y, 2)) * acos(beta);
	d2 = sqrt(pow(e->px - (w2)->x, 2) + pow(e->py - (w2)->y, 2)) * acos(beta);

	// free(w2);
	// free(w1);
	if (d1 < d2)
	{
		set_color_based_on_pos(e, (w1));
		return d1;
	}
	set_color_based_on_pos(e, (w2));
	return d2;
}

void draw(t_env *e) {
	// e->startTime = time(NULL);
	gettimeofday(&e->startTime, NULL);
	int col = -1;
	double inc = 60.0 / 640.0;
	double deg = 0;
	double beta = 0;
	double dist;
	double slice_height;
	int projection_dist = 277;
	t_pos_i *w1;
	t_pos_i *w2;

	while (++col < e->w_width) {
		printf("col: %d\n", col);
		printf("deg: %.2f\n", deg);
		// beta = deg < 30 ? 90 - (30 - deg) : 90 - (deg - 30);
		printf("beta: %.2f\n", beta);
		// printf("%s\n", );

		// ;
		// cast ray and get distance to a wall;
		// beta = deg > 30 ? deg - 30 : deg;
		// beta = deg;
		// printf("hor wall\n");
		w1 = get_hor_wall(e, beta);
		printf("ver wall\n");
		w2 = get_ver_wall(e, beta);
		printf("dist\n");
		dist = get_closest_dist(e, beta, w1, w2);
		printf("free\n");
		free(w1);
		free(w2);
		printf("slice_height\n");
		slice_height = ceil(64.0 / dist * projection_dist);

		printf("create drawing points\n");
		t_point start;
		start.x = col;
		start.y = 100 - slice_height / 2;

		t_point end;
		end.x = col;
		end.y = 100 + slice_height / 2;

		printf("draw line\n");
		draw_line(e, start, end, e->color);
		deg += inc;
	}
	printf("pos: %d, %d\n", e->px, e->py);
	// draw_point_to_img(e, x, y, e->buffer[y][x]);
	// mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);

	// for(int x = 0; x < e->w_width; x++)
 //    	for(int y = 0; y < e->w_height; y++)
 //    		draw_point_to_img(e, x, y, 0);
	// draw_buffer(e);
    // for(int x = 0; x < e->w_width; x++)
    // 	for(int y = 0; y < e->w_height; y++)
    // 		e->buffer[y][x] = 0; //clear the buffer instead of cls()

	// e->endTime = time(NULL);
	gettimeofday(&e->endTime, NULL);
	long double frameTime = fabs((e->endTime.tv_usec - e->startTime.tv_usec) / 1000000.0);
	printf("Time: %Lf\n", 1.0 / frameTime);
	// printf("Time 2: %f\n", e->endTime - e->startTime);
	//speed modifiers
    e->moveSpeed = frameTime * 50.0; //the constant value is in squares/second
    e->rotSpeed = frameTime * 30.0; //the constant value is in radians/second
}

int	key_handler(int keycode, t_env *e)
{
	printf("%d\n", keycode);
    // W
	if (keycode == 13 || keycode == 126)
	{
		// printf("world: %d, %d\n", e->px + e->dir_x * e->moveSpeed, e->py);
		if(worldMap[(int)(e->px + e->dir_x * e->moveSpeed)][(int)(e->py)] == 0)
			e->px += e->dir_x * e->moveSpeed;
		if(worldMap[(int)(e->px)][(int)(e->py + e->dir_y * e->moveSpeed)] == 0)
			e->py += e->dir_y * e->moveSpeed;
	}
	// A
	if (keycode == 0 || keycode == 123)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = e->dir_x;
		e->dir_x = e->dir_x * cos(e->rotSpeed) - e->dir_y * sin(e->rotSpeed);
		e->dir_y = oldDirX * sin(e->rotSpeed) + e->dir_y * cos(e->rotSpeed);
		double oldPlaneX = e->planeX;
		e->planeX = e->planeX * cos(e->rotSpeed) - e->planeY * sin(e->rotSpeed);
		e->planeY = oldPlaneX * sin(e->rotSpeed) + e->planeY * cos(e->rotSpeed);
	}
	// S
	if (keycode == 1 || keycode == 125)
	{
		if(worldMap[(int)(e->px - e->dir_x * e->moveSpeed)][(int)(e->py)] == 0)
			e->px -= e->dir_x * e->moveSpeed;
      	if(worldMap[(int)(e->px)][(int)(e->py - e->dir_y * e->moveSpeed)] == 0)
      		e->py -= e->dir_y * e->moveSpeed;
	}
	// D
	if (keycode == 2 || keycode == 124)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = e->dir_x;
		e->dir_x = e->dir_x * cos(-e->rotSpeed) - e->dir_y * sin(-e->rotSpeed);
		e->dir_y = oldDirX * sin(-e->rotSpeed) + e->dir_y * cos(-e->rotSpeed);
		double oldPlaneX = e->planeX;
		e->planeX = e->planeX * cos(-e->rotSpeed) - e->planeY * sin(-e->rotSpeed);
		e->planeY = oldPlaneX * sin(-e->rotSpeed) + e->planeY * cos(-e->rotSpeed);
	}

	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->w_width, e->w_height);

	draw(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return 0;
}

int main(int ac, char **av)
{
	double posX = 22;
	double posY = 12;
	double dirX = -1;
	double dirY = 0;
	double planeX = 0;
	double planeY = 0.66;


	// double time = 0;
	// double oldTime = 0;
	
	// struct timespec start, end;
	// clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	t_env env;
	env.w_width = screenWidth;
	env.w_height = screenHeight;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, env.w_width, env.w_height, "Wolf3D");
	env.img = mlx_new_image(env.mlx, env.w_width, env.w_height);
	
	env.img_ptr = mlx_get_data_addr((void *)env.img, &(env.bpp),
		&(env.line_size), &(env.endian));

	env.posX = 22;
	env.posY = 12;
	env.dirX = -1;
	env.dirY = 0;
	env.planeX = 0;
	env.planeY = 0.66;
	env.tex_width = 64;
	env.tex_height = 64;
	env.px = 22;
	env.py = 12;
	env.dir_x = -1;
	env.dir_y = 0;


	// unsigned int buffer[env.w_height][env.w_width]; // y-coordinate first because it works per scanline
	// int texture[8][env.tex_width * env.tex_height];
	// for(int i = 0; i < 8; i++)
	// 	texture[i].resize(env.tex_width * env.tex_height);

	//generate some textures
	printf("textures\n");
	env.buffer = (unsigned int**)malloc(sizeof(int*) * screenHeight);
	for (int i = 0; i < screenHeight; i++) {
		env.buffer[i] = (unsigned int*)malloc(sizeof(int) * screenWidth);
	}

	env.texture = (int**)malloc(sizeof(int*) * 8);
	for(int i = 0; i < 8; i++) {
		env.texture[i] = (int*)malloc(sizeof(int) * (env.tex_width * env.tex_height ));
	}
	for(int x = 0; x < env.tex_width; x++)
	for(int y = 0; y < env.tex_height; y++)
	{
		int xorcolor = (x * 256 / env.tex_width) ^ (y * 256 / env.tex_height);
		//int xcolor = x * 256 / env.tex_width;
		int ycolor = y * 256 / env.tex_height;
		int xycolor = y * 128 / env.tex_height + x * 128 / env.tex_width;
		env.texture[0][env.tex_width * y + x] = 65536 * 254 * (x != y && x != env.tex_width - y); //flat red texture with black cross
		env.texture[1][env.tex_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
		env.texture[2][env.tex_width * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
		env.texture[3][env.tex_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
		env.texture[4][env.tex_width * y + x] = 256 * xorcolor; //xor green
		env.texture[5][env.tex_width * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
		env.texture[6][env.tex_width * y + x] = 65536 * ycolor; //red gradient
		env.texture[7][env.tex_width * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	}

	ft_printf("drawing\n");
	draw(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	

	// mlx_hook(pe->env.win, 6, 1, drag, e);
	// time_t startTime = time(NULL);
	// time_t endTime = time(NULL);
	// gettimeofday(&stop, NULL);
	// uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	// ft_printf("%d", delta_us);
	// int i = 0;
	// while (i < 1000000000)
	// {
	// 	i++;
	// }
	
	
	// t_point start;
	//   start.x = 0;
	//   start.y = 0;

	//   t_point end;
	//   end.x = 200;
	//   end.y = 200;
	// draw_line(&env, start, end, 0xFFFFFF);

	// draw(&env);
	mlx_hook(env.win, 2, 1, key_handler, &env);
	// mlx_key_hook(env.win, key_handler, &env);
	mlx_loop(env.mlx);

	
	ac = 0;
	av = 0;
	return (0);
}