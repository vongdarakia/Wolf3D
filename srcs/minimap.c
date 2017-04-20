#include "wolf3d.h"



double	get_side_dist(double pos, double dir, int map, double dlt_dist)
{
	if (dir < 0)
	{
		return (pos - map) * dlt_dist;
	}
	return (map + 1.0 - pos) * dlt_dist;
}

void	shoot_ray(t_env *e, t_point *ray)
{
	e->hit = 0;

	double y2 = e->dir.y * e->dir.y;
	double x2 = e->dir.x * e->dir.x;
	e->dlt_dist.x = sqrt(1 + (y2 / x2));
	e->dlt_dist.y = sqrt(1 + (x2 / y2));

	printf("%.2f %.2f %d %.2f\n", e->pos.x, e->dirX, e->map.y, e->dlt_dist.x);
	e->side_dist.x = get_side_dist(e->pos.x, e->dirX, e->map.x, e->dlt_dist.x);
	e->side_dist.y = get_side_dist(e->pos.y, e->dirY, e->map.y, e->dlt_dist.y);
	// printf("side %.1f %.1f\n", e->dlt_dist.x, e->dlt_dist.y);
	// printf("side %.1f %.1f\n", e->side_dist.x, e->side_dist.y);
	// while (e->hit == 0 && (e->map.x < e->m_width || e->map.y < e->m_height))
	// {
	// 	if (e->side_dist.x < e->side_dist.y)
	// 	{
	// 		e->side_dist.x += e->dlt_dist.x;
	// 		e->map.x += e->dirX;
	// 		e->side = 0;
	// 	}
	// 	else
	// 	{
	// 		e->side_dist.y += e->dlt_dist.y;
	// 		e->map.y += e->dirY;
	// 		e->side = 1;
	// 	}
	// 	if (e->w_map[e->map.x][e->map.y] > 0)
	// 		e->hit = 1;
	// }
}

void	shoot_rays(t_env *e)
{
	double x;
	double cam_x;
	double screen_w;
	t_point ray;

	screen_w = (double)(screenWidth);
	x = 0.0;
	while (++x < screen_w)
	{
		cam_x = 2 * x / screen_w - 1;
		// printf("%.2f\n", cam_x);
		ray.x = e->dir.x + e->plane.x * cam_x;
		ray.y = e->dir.y + e->plane.y * cam_x;
		shoot_ray(e, &ray);

		ray.x += e->pos.x;
		ray.y += e->pos.y;
		draw_line(e, e->pos, ray, 0xFFFFFF);
	}
	
}

void	draw_map(t_env *e)
{
	// mapWidth
	int y = -1;
	int x = 0;
	int r = -1;
	int c = 0;

	// printf("map %d %d\n", e->m_width, e->m_height);
	while (++r < e->m_height)
	{
		c = -1;
		while (++c < e->m_width)
		{
			// printf("(%d %d) %d\n", r, c, e->w_map[r][c]);
			if (e->w_map[r][c] > 0) {
				y = -1;
				while (++y < mapWidth)
				{
					x = -1;
					while (++x < mapWidth)
					{
						draw_point_to_img(e, x + c * mapWidth, y + r * mapWidth, 0xF0F0F0);		
					}
				}
			}
		}
	}
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

	draw_map(e);
	shoot_rays(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);

	double y2 = e->dir.y * e->dir.y;
	double x2 = e->dir.x * e->dir.x;
	e->dlt_dist.x = sqrt(1 + (y2) / (x2));
	e->dlt_dist.y = sqrt(1 + (x2) / (y2));
	e->map.x = (int)(e->pos.x / mapWidth);
	e->map.y = (int)(e->pos.y / mapWidth);
	printf("map %.2f %.2f\n", e->pos.x, e->pos.y);
	// printf("dlt_dist x y (%.2f, %.2f)\n", e->dlt_dist.x, e->dlt_dist.y);
	// printf("dlt_dist x y (%.2f, %.2f)\n", e->dlt_dist.x, e->dlt_dist.y);
	// e->side_dist.x = get_side_dist(e->pos.x, e->dirX, e->map.x, e->dlt_dist.x);
	// e->side_dist.y = get_side_dist(e->pos.y, e->dirX, e->map.y, e->dlt_dist.y);
	// printf("side x y (%.2f, %.2f)\n", e->side_dist.x, e->side_dist.y);
}