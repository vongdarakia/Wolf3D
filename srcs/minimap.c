#include "wolf3d.h"

void	shoot_ray(t_env *e)
{

}

void	draw_minimap(t_env *e)
{
	// printf("Drawing\n");
	t_point start;
	start.x = 0.0;
	start.y = 0.0;
	t_point end;
	end.x = e->dir.x + e->pos.x;
	end.y = e->dir.y + e->pos.y;

	
	// env.plane_r.y = env.dir.y + env.pos.y;

	// env.plane_l.x = env.dir.x + env.pos.x - env.dir.y * tan(M_PI * fov / 360.0);
	// env.plane_l.y = env.plane_r.y;

	// double degree = 45.0;
	// double len = tan(M_PI * degree / 180.0) * 2.0;
	// draw_line(e, end, e->plane_r, 0xFFFFFF);
	// draw_line(e, end, e->plane_l, 0xFFFFFF);

	// draw_line(e, e->pos, e->plane_l, 0xFFFFFF);
	// draw_line(e, e->pos, e->plane_r, 0xFFFFFF);

	t_point plane;
	plane.x = e->dir.x + e->pos.x + e->plane.x;
	plane.y = e->dir.y + e->pos.y + e->plane.y;
	draw_line(e, end, plane, 0xFFFFFF);
	draw_line(e, e->pos, plane, 0xFFFFFF);

	plane.x = e->dir.x + e->pos.x - e->plane.x;
	plane.y = e->dir.y + e->pos.y - e->plane.y;

	draw_line(e, end, plane, 0xFFFFFF);
	draw_line(e, e->pos, plane, 0xFFFFFF);



	draw_line(e, e->pos, end, 0xFFFFFF);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}