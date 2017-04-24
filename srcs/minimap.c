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

	double y2 = ray->y * ray->y;
	double x2 = ray->x * ray->x;

	// printf("%.2f %.2f\n", e->dir.y, e->dir.x);
	e->dlt_dist.x = sqrt(1 + (y2 / x2));
	e->dlt_dist.y = sqrt(1 + (x2 / y2));

	// printf("%.2f %.2f %d %.2f\n", e->pos.x, ray->x, e->map.y, e->dlt_dist.x);

	e->side_dist.x = get_side_dist(e->pos.x, ray->x, e->map.x, e->dlt_dist.x);
	e->side_dist.y = get_side_dist(e->pos.y, ray->y, e->map.y, e->dlt_dist.y);
	// double dist = sqrt(y2 + x2);
	// if (e->map.x * mapWidth - e->pos.x == 0) {
		
	// }
	// e->map.x += e->dirX;
	// e->map.y += e->dirY;
	// if (e->map.y * mapWidth - e->pos.y == 0) {
		
	// }
	// e->side_dist.x = dist * (e->map.x * mapWidth - e->pos.x) / (ray->x);
	// e->side_dist.y = dist * (e->map.y * mapHeight - e->pos.y) / (ray->y);

	// printf("dist %.1f\n", dist);
	// printf("dlt %.1f %.1f\n", e->dlt_dist.x, e->dlt_dist.y); 
	// printf("pos %.1f %.1f\n", e->pos.x, e->pos.y);
	printf("map %d %d\n", e->map.x, e->map.y);
	// printf("side x (%.1f) / %.1f = %.1f * %.1f = %.f\n", (e->map.x * mapWidth - e->pos.x), ray->x, dist, (e->map.x * mapWidth - e->pos.x) / ray->x, e->side_dist.x);
	// printf("side y (%.1f) / %.1f = %.1f\n", (e->map.y * mapWidth - e->pos.y), ray->y, e->side_dist.y);
	printf("side %.1f %.1f\n", e->side_dist.x, e->side_dist.y);
	while (e->hit == 0 && (e->map.x < e->m_width || e->map.y < e->m_height))
	{
		if (e->side_dist.x < e->side_dist.y)
		{
			e->side_dist.x += e->dlt_dist.x;
			e->map.x += e->dirX;
			e->side = 0;
		}
		else
		{
			e->side_dist.y += e->dlt_dist.y;
			e->map.y += e->dirY;
			e->side = 1;
		}
		if (e->w_map[e->map.x][e->map.y] > 0)
			e->hit = 1;
	}
	printf("hit at %d %d\n", e->map.x, e->map.y);
	// if (e->map.x == e->m_width)
	// 	e->map.x -= 1;
	// if (e->map.y == e->m_height)
	// 	e->map.y -= 1;

}

void	shoot_rays(t_env *e)
{
	double x;
	double cam_x;
	double screen_w;
	t_point ray;
	t_point start;
	start.x = e->pos.x * mapWidth;
	start.y = e->pos.y * mapWidth;


	screen_w = (double)(screenWidth);
	x = 0.0;

	while (++x < screen_w)
	{
		cam_x = 2 * x / screen_w - 1;
		// printf("%.2f\n", e->plane.x);
		ray.x = (e->dir.x + e->plane.x * cam_x);
		ray.y = (e->dir.y + e->plane.y * cam_x);
		e->map.x = (int) (e->pos.x);
		e->map.y = (int) (e->pos.y);
		shoot_ray(e, &ray);

		// ray.x = ray.x * e->dir_len + start.x;
		// ray.y = ray.y * e->dir_len + start.y;
		ray.x += (e->map.x - 1) * mapWidth;
		ray.y += (e->map.y + 1) * mapHeight;
		// ray.x = e->map.x + e->plane.x * cam_x;
		// ray.y = e->map.y + e->plane.y * cam_x;
		// printf("ray %.2f, %2.f\n", ray.x, ray.y);
		draw_line(e, start, ray, 0xFFFFFF);
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
	start.x = e->pos.x * mapWidth;
	start.y = e->pos.y * mapWidth;
	t_point end;
	end.x = e->dir.x * e->dir_len + e->pos.x * mapWidth;
	end.y = e->dir.y * e->dir_len + e->pos.y * mapHeight;

	
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
	plane.x = (e->dir.x + e->plane.x) * e->dir_len + e->pos.x * mapWidth;
	plane.y = (e->dir.y + e->plane.y) * e->dir_len + e->pos.y * mapHeight;

	printf("plane %.1f %.1f\n", plane.x, plane.y);
	draw_line(e, end, plane, 0xFFFFFF);
	draw_line(e, start, plane, 0xFFFFFF);

	plane.x = (e->dir.x - e->plane.x) * e->dir_len + e->pos.x * mapWidth;
	plane.y = (e->dir.y - e->plane.y) * e->dir_len + e->pos.y * mapHeight;

	draw_line(e, end, plane, 0xFFFFFF);
	draw_line(e, start, plane, 0xFFFFFF);



	draw_line(e, start, end, 0xFFFFFF);

	

	double y2 = e->dir.y * e->dir.y;
	double x2 = e->dir.x * e->dir.x;
	e->dlt_dist.x = sqrt(1 + (y2) / (x2));
	e->dlt_dist.y = sqrt(1 + (x2) / (y2));
	e->map.x = (int)(e->pos.x);
	e->map.y = (int)(e->pos.y);
	

	draw_map(e);
	shoot_rays(e);
	printf("map %.2f %.2f\n", e->pos.x, e->pos.y);
	printf("map %.2f / %d = %.2f == %d\n", e->pos.y, mapWidth, e->pos.y, e->map.y);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);

	// printf("dlt_dist x y (%.2f, %.2f)\n", e->dlt_dist.x, e->dlt_dist.y);
	// printf("dlt_dist x y (%.2f, %.2f)\n", e->dlt_dist.x, e->dlt_dist.y);
	// e->side_dist.x = get_side_dist(e->pos.x, e->dirX, e->map.x, e->dlt_dist.x);
	// e->side_dist.y = get_side_dist(e->pos.y, e->dirX, e->map.y, e->dlt_dist.y);
	// printf("side x y (%.2f, %.2f)\n", e->side_dist.x, e->side_dist.y);
}