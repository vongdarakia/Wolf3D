/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:00:07 by avongdar          #+#    #+#             */
/*   Updated: 2017/05/04 18:00:26 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_color(t_env *e)
{
	if (e->w_map[e->map.x][e->map.y] > 0)
	{
		if (e->side == SIDE_Y)
			return (e->ray_dir.y > 0 ? RED : BLUE);
		else
			return (e->ray_dir.x > 0 ? GREEN : YELLOW);
	}
	return (WHITE);
}
