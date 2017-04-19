#include "wolf3d.h"

int	key_handler(int keycode, t_env *e)
{
	// printf("%d\n", keycode);
	if (keycode == W || keycode == UP)
	{
		e->pos.y -= 5;
	}
	if (keycode == A || keycode == LEFT)
	{
		double old_x = e->dir.x;
		double speed = -0.1;
		e->dir.x = e->dir.x * cos(speed) - e->dir.y * sin(speed);
		e->dir.y = old_x * sin(speed) + e->dir.y * cos(speed);

		old_x = e->plane_r.x;
		e->plane_r.x = e->plane_r.x * cos(speed) - e->plane_r.y * sin(speed);
		e->plane_r.y = old_x * sin(speed) + e->plane_r.y * cos(speed);

		old_x = e->plane_l.x;
		e->plane_l.x = e->plane_l.x * cos(speed) - e->plane_l.y * sin(speed);
		e->plane_l.y = old_x * sin(speed) + e->plane_l.y * cos(speed);

		old_x = e->plane.x;
		e->plane.x = e->plane.x * cos(speed) - e->plane.y * sin(speed);
		e->plane.y = old_x * sin(speed) + e->plane.y * cos(speed);
		// double oldPlaneX = e->planeX;
		// e->planeX = e->planeX * cos(e->rotSpeed) - e->planeY * sin(e->rotSpeed);
		// e->planeY = oldPlaneX * sin(e->rotSpeed) + e->planeY * cos(e->rotSpeed);
	}
	if (keycode == S || keycode == DOWN)
	{
		e->pos.y += 5;
	}
	if (keycode == D || keycode == RIGHT)
	{
		double old_x = e->dir.x;
		double speed = 0.1;
		e->dir.x = e->dir.x * cos(speed) - e->dir.y * sin(speed);
		e->dir.y = old_x * sin(speed) + e->dir.y * cos(speed);

		old_x = e->plane.x;
		e->plane.x = e->plane.x * cos(speed) - e->plane.y * sin(speed);
		e->plane.y = old_x * sin(speed) + e->plane.y * cos(speed);
	}
	if (keycode == ESC)
	{
		exit(0);
	}
	// printf("keycode %d\n", keycode);
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, e->w_width, e->w_height);

	draw_minimap(e);

	// mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return 0;
}

int main(int ac, char **av)
{
	double dirX = -1;
	double dirY = 0;
	double planeX = 0;
	double planeY = 0.66;

	t_env env;
	env.w_width = screenWidth;
	env.w_height = screenHeight;
	// if (ac > 1)
	// 	read_map(&env, av[1]);
	// else
	// 	read_map(&env, "map1.txt");

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, screenWidth, screenHeight, "Wolf3D");
	env.img = mlx_new_image(env.mlx, screenWidth, screenHeight);
	env.img_ptr = mlx_get_data_addr((void *)env.img, &(env.bpp),
		&(env.line_size), &(env.endian));

	printf("%d %d %d\n", env.bpp, env.line_size, env.endian);
	env.ray_pos.x = 22;
	env.ray_pos.y = 12;
	env.dirX = -1;
	env.dirY = 0;
	env.planeX = 0;
	env.planeY = 0.66;
	env.tex_width = 64;
	env.tex_height = 64;
	env.pos.x = screenWidth / 2;
	env.pos.y = screenHeight / 2;
	env.dir.x = 0;
	env.dir.y = 100;
	double fov = 60.0;

	// env.plane_r.x = env.dir.x + env.pos.x + env.dir.y * tan(M_PI * fov / 360.0);
	// env.plane_r.y = env.dir.y + env.pos.y;

	// env.plane_l.x = env.dir.x + env.pos.x - env.dir.y * tan(M_PI * fov / 360.0);
	// env.plane_l.y = env.plane_r.y;

	env.plane.x = env.dir.y * tan(M_PI * fov / 360.0);
	env.plane.y = 0;

	printf("plane %.2f %.2f\n", env.plane_r.x, env.plane_r.y);
	draw_minimap(&env);
	// t_point start;
	// start.x = 50;
	// start.y = 50;
	t_point end;
	end.x = env.pos.x + env.dir.x;
	end.y = env.pos.y + env.dir.y;
	printf("%.2f %.2f\n", end.x, end.y);
	draw_line(&env, env.pos, end, 0xFFFFFF);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	mlx_hook(env.win, 2, 1, key_handler, &env);
	mlx_loop(env.mlx);
	
	ac = 0;
	av = 0;
	return (0);
}