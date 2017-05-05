/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 14:12:21 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/09 14:12:23 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_point_to_img(t_env *e, int x, int y, int color)
{
	x = x * e->bpp / 8;
	y = y * e->line_size;
	e->img_ptr[x++ + y] = color % 256;
	e->img_ptr[x++ + y] = (color /= 256) % 256;
	e->img_ptr[x + y] = (color /= 256) % 256;
}

void	draw_line_xslope(t_env *e, t_point p0, t_point p1, int color)
{
	int		pitch;
	double	m;
	t_point	p;

	m = (p1.y - p0.y) / (p1.x - p0.x);
	pitch = p0.y - m * p0.x;
	p0.x += p0.x > p1.x ? 1 : -1;
	if (p0.x > p1.x)
		while (--(p0.x) >= p1.x)
		{
			p.y = m * p0.x + pitch;
			if (p0.x < e->w_width && p0.x >= 0
				&& p.y < e->w_height && p.y >= 0)
				draw_point_to_img(e, p0.x, p.y, color);
		}
	else
		while (++(p0.x) <= p1.x)
		{
			p.y = m * p0.x + pitch;
			if (p.y < e->w_width && p.y >= 0
				&& p0.x < e->w_height && p0.x >= 0)
				draw_point_to_img(e, p0.x, p.y, color);
		}
}

void	draw_line_yslope(t_env *e, t_point p0, t_point p1, int color)
{
	int		pitch;
	double	m;
	t_point	p;

	m = (p1.x - p0.x) / (p1.y - p0.y);
	pitch = p0.x - m * p0.y;
	p0.y += p0.y > p1.y ? 1 : -1;
	if (p0.y >= p1.y)
		while (--(p0.y) >= p1.y)
		{
			p.x = (m * p0.y + pitch);
			if (p0.y >= 0 && p0.y < e->w_height
				&& p.x >= 0 && p.x < e->w_width)
				draw_point_to_img(e, p.x, p0.y, color);
		}
	else
		while (++(p0.y) <= p1.y)
		{
			p.x = (m * p0.y + pitch);
			if (p0.y >= 0 && p0.y < e->w_height
				&& p.x >= 0 && p.x < e->w_width)
				draw_point_to_img(e, p.x, p0.y, color);
		}
}

void	draw_line(t_env *e, t_point p0, t_point p1, int color)
{
	if (p0.x == p1.x && p0.y == p1.y)
		draw_point_to_img(e, p0.x, p0.y, color);
	else if (ABS(p1.y - p0.y) <= ABS(p1.x - p0.x))
		draw_line_xslope(e, p0, p1, color);
	else
		draw_line_yslope(e, p0, p1, color);
}

void	draw_buffer(t_env *e)
{
	int	y;
	int	x;

	x = -1;
	while (++x < e->w_width)
	{
		y = -1;
		while (++y < e->w_height)
		{
			draw_point_to_img(e, x, y, e->buffer[y][x]);
		}
	}
}
