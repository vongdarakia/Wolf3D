/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 14:06:20 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/09 14:06:22 by avongdar         ###   ########.fr       */
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

void	exit_with_error(int fd, char *msg)
{
	close(fd);
	printf("%s\n", msg);
	exit(1);
}

void	create_map_from_file(int fd, t_env *e)
{
	char	**row;
	char	*line;
	int		i;
	int		j;

	i = -1;
	e->w_map = (int**)malloc(sizeof(int*) * e->m_height);
	while (get_next_line(fd, &line) == 1)
	{
		e->w_map[++i] = (int*)malloc(sizeof(int) * e->m_width);
		row = ft_strsplit(line, ',');
		j = -1;
		while (++j < e->m_width)
		{
			if (is_str_numeric(row[j]))
				e->w_map[i][j] = ft_atoi(row[j]);
			else
				exit_with_error(fd, "Invalid map");
		}
	}
}

void	read_map(t_env *e, char *filename)
{
	int		fd;
	char	*line;
	char	**row;
	int		is_bad;

	e->m_width = -1;
	e->m_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		while (get_next_line(fd, &line) == 1)
		{
			row = ft_strsplit(line, ',');
			if (e->m_width == -1)
				e->m_width = get_width(row);
			else if (get_width(row) != e->m_width)
				exit_with_error(fd, "Invalid map");
			e->m_height++;
		}
		close(fd);
		fd = open(filename, O_RDONLY);
		create_map_from_file(fd, e);
		close(fd);
	}
}
