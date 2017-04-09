/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 14:32:12 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/09 14:32:15 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	cast_ray(t_env *e)
{
	e->hit = 0;
	while (e->hit == 0)
	{
		if (e->side_dist.x < e->side_dist.y)
		{
			e->side_dist.x += e->dlt_dist.x;
			e->map.x += e->step.x;
			e->side = 0;
		}
		else
		{
			e->side_dist.y += e->dlt_dist.y;
			e->map.y += e->step.y;
			e->side = 1;
		}
		if (e->w_map[e->map.x][e->map.y] > 0)
			e->hit = 1;
	}
}

int		get_wall_height(t_env *e)
{
	double	wall_dist;
	double		y2;
	double		x2;

	y2 = e->ray_dir.y * e->ray_dir.y;
	x2 = e->ray_dir.x * e->ray_dir.x;
	e->dlt_dist.x = sqrt(1 + (y2) / (x2));
	e->dlt_dist.y = sqrt(1 + (x2) / (y2));
	e->map.x = (int)(e->ray_pos.x);
	e->map.y = (int)(e->ray_pos.y);
	e->step.x = (e->ray_dir.x < 0) ? -1 : 1;
	e->side_dist.x = (e->ray_dir.x < 0) ? (e->ray_pos.x - e->map.x)
		* e->dlt_dist.x : (e->map.x + 1.0 - e->ray_pos.x) * e->dlt_dist.x;
	e->step.y = (e->ray_dir.y < 0) ? -1 : 1;
	e->side_dist.y = (e->ray_dir.y < 0) ? (e->ray_pos.y - e->map.y)
		* e->dlt_dist.y : (e->map.y + 1.0 - e->ray_pos.y) * e->dlt_dist.y;
	cast_ray(e);
	if (e->side == 0)
		wall_dist = (e->map.x - e->ray_pos.x
			+ (1 - e->step.x) / 2) / e->ray_dir.x;
	else
		wall_dist = (e->map.y - e->ray_pos.y
			+ (1 - e->step.y) / 2) / e->ray_dir.y;
	return (int)(e->w_height / wall_dist);
}

void	draw_rays(t_env *e) {
	int	draw_start;
	int	draw_end;
	int	x;

	gettimeofday(&e->startTime, NULL);
	x = -1;
	while (++x < e->w_width)
	{
		e->cameraX = 2 * x / (double)(e->w_width) - 1;
		e->ray_dir.x = e->dirX + e->planeX * e->cameraX;
		e->ray_dir.y = e->dirY + e->planeY * e->cameraX;
		e->line_height = get_wall_height(e);
		draw_start = -e->line_height / 2 + e->w_height/ 2;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = e->line_height / 2 + e->w_height/ 2;
		if(draw_end >= e->w_height)
			draw_end = e->w_height- 1;
		//choose wall color
		// int color;
		// switch (e->w_map[e->map.x][e->map.y])
		// {
		// 	case 1:  color = 0xFF0000;  break; //red
		// 	case 2:  color = 0x00FF00;  break; //green
		// 	case 3:  color = 0x0000FF;   break; //blue
		// 	case 4:  color = 0xFFFFFF;  break; //white
		// 	default: color = 0xFFFF00; break; //yellow
		// }

		//give x and y e->sides different brightness
		// if (e->side == 1) {color = color / 2;}
		t_point start;
		start.x = x;
		start.y = draw_start;
		t_point end;
		end.x = x;
		end.y = draw_end;
		draw_line(e, start, end, 0xFFFFFF);
	}

	gettimeofday(&e->endTime, NULL);
	long double frameTime = fabs((e->endTime.tv_usec - e->startTime.tv_usec) / 1000000.0);
	printf("Time: %Lf\n", 1.0 / frameTime);
    e->moveSpeed = frameTime * 50.0; //the constant value is in squares/second
    e->rotSpeed = frameTime * 30.0; //the constant value is in radians/second
}
