/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:22:39 by avongdar          #+#    #+#             */
/*   Updated: 2017/05/04 19:22:41 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_point	point(int x, int y)
{
	t_point p;

	p.x = x;
	p.y = y;
	return (p);
}

t_pos_i	pos_i(int x, int y)
{
	t_pos_i p;

	p.x = x;
	p.y = y;
	return (p);
}

t_pos_f	pos_f(double x, double y)
{
	t_pos_f p;

	p.x = x;
	p.y = y;
	return (p);
}
