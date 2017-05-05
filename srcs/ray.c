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

void	set_wall_height(t_env *e)
{
	e->y2 = e->ray_dir.y * e->ray_dir.y;
	e->x2 = e->ray_dir.x * e->ray_dir.x;
	e->dlt_dist.x = sqrt(1 + (e->y2) / (e->x2));
	e->dlt_dist.y = sqrt(1 + (e->x2) / (e->y2));
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
		e->wall_dist = (e->map.x - e->ray_pos.x
			+ (1 - e->step.x) / 2) / e->ray_dir.x;
	else
		e->wall_dist = (e->map.y - e->ray_pos.y
			+ (1 - e->step.y) / 2) / e->ray_dir.y;
	e->line_height = (int)(e->w_height / e->wall_dist);
}

void	set_texture(t_env *e)
{
	e->tex_num = e->w_map[e->map.x][e->map.y] - 1;
	if (e->side == 0)
		e->wall_x = e->ray_pos.y + e->wall_dist * e->ray_dir.y;
	else
		e->wall_x = e->ray_pos.x + e->wall_dist * e->ray_dir.x;
	e->wall_x -= floor(e->wall_x);
	e->tex.x = (int)(e->wall_x * (double)(e->tex_width));
	if (e->side == 0 && e->ray_dir.x > 0)
		e->tex.x = e->tex_width - e->tex.x - 1;
	if (e->side == 1 && e->ray_dir.y < 0)
		e->tex.x = e->tex_width - e->tex.x - 1;
}

void	draw_texture(t_env *e)
{
	set_texture(e);
	e->y = e->draw_start;
	while (e->y < e->draw_end)
	{
		e->d = e->y * 256 - e->w_height * 128 + e->line_height * 128;
		e->tex.y = ((e->d * e->tex_height) / e->line_height) / 256;
		e->color = e->texture[e->tex_num][e->tex_height * e->tex.y + e->tex.x];
		if (e->side == 1)
			e->color = (e->color >> 1) & 8355711;
		e->buffer[e->y][e->x] = e->color;
		draw_point_to_img(e, e->x, e->y, e->color);
		e->y++;
	}
}

void	draw_rays(t_env *e)
{
	e->x = -1;
	while (++(e->x) < e->w_width)
	{
		e->cameraX = 2 * e->x / (double)(e->w_width) - 1;
		e->ray_dir.x = e->dir.x + e->plane.x * e->cameraX;
		e->ray_dir.y = e->dir.y + e->plane.y * e->cameraX;
		set_wall_height(e);
		e->draw_start = -e->line_height / 2 + e->w_height / 2;
		if (e->draw_start < 0)
			e->draw_start = 0;
		e->draw_end = e->line_height / 2 + e->w_height / 2;
		if (e->draw_end >= e->w_height)
			e->draw_end = e->w_height - 1;
		draw_texture(e);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}
