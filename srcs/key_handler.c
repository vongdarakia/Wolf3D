#include "wolf3d.h"

/*
**	Moves the player forwards or backwards
*/

void	move_straight(t_env *e, double speed)
{
	int new_x;
	int new_y;

	new_x = (int)(e->ray_pos.x + e->dir.x * speed);
	new_y = (int)(e->ray_pos.y);
	if (e->w_map[new_x][new_y] == 0)
		e->ray_pos.x += e->dir.x * speed;
	new_y = (int)(e->ray_pos.y + e->dir.y * speed);
	new_x = (int)(e->ray_pos.x);
	if (e->w_map[new_x][new_y] == 0)
		e->ray_pos.y += e->dir.y * speed;
}

/*
**	Rotates both camera direction and camera plane.
*/

void	rotate(t_env *e, double rot_spd)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = e->dir.x;
	e->dir.x = e->dir.x * cos(rot_spd) - e->dir.y * sin(rot_spd);
	e->dir.y = old_dir_x * sin(rot_spd) + e->dir.y * cos(rot_spd);
	old_plane_x = e->plane.x;
	e->plane.x = e->plane.x * cos(rot_spd) - e->plane.y * sin(rot_spd);
	e->plane.y = old_plane_x * sin(rot_spd) + e->plane.y * cos(rot_spd);
}

int		key_pressed(int keycode, t_env *e)
{
	e->keys[keycode] = 1;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int		key_released(int keycode, t_env *e)
{
	e->keys[keycode] = 0;
	return (0);
}

int		loop_hook(t_env *e)
{
	// clock_t	end = clock();
	// frame_time = ((double)(end - e->));
	// double frame_time = fabs((double)(e->prev_time - end) / CLOCKS_PER_SEC);
	// printf("frame_time: %f\n", frame_time);
	// e->prev_time = end;
	// e->move_spd = frame_time * 20.0;
	// e->rot_spd = frame_time * 15.0;
	if (e->keys[KEY_W] || e->keys[KEY_UP])
		move_straight(e, e->move_spd);
	if (e->keys[KEY_A] || e->keys[KEY_LEFT])
		rotate(e, e->rot_spd);
	if (e->keys[KEY_S] || e->keys[KEY_DOWN])
		move_straight(e, -e->move_spd);
	if (e->keys[KEY_D] || e->keys[KEY_RIGHT])
		rotate(e, -e->rot_spd);
	if (e->keys[KEY_D] || e->keys[KEY_RIGHT] || e->keys[KEY_S]
		|| e->keys[KEY_DOWN] || e->keys[KEY_A] || e->keys[KEY_LEFT]
		|| e->keys[KEY_W] || e->keys[KEY_UP])
	{
		mlx_destroy_image(e->mlx, e->img);
		e->img = mlx_new_image(e->mlx, e->w_width, e->w_height);
		// draw_rays_with_fps(e);
		// draw_minimap(e);
		draw_rays(e);
	}
	return (0);
}