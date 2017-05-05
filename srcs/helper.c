/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:02:41 by avongdar          #+#    #+#             */
/*   Updated: 2017/05/04 22:02:42 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		is_str_numeric(char *str)
{
	int i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

int		get_width(char **words)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}

void	free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_mapn(char **map, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
