/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 13:25:43 by avongdar          #+#    #+#             */
/*   Updated: 2016/10/07 13:26:03 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		copy_until_nline(char **p_line, char *left_overs, int *pos, int *ret)
{
	int		i;
	char	*line;

	i = 0;
	while (left_overs[i] && left_overs[i] != '\n')
		i++;
	line = ft_strrealloc(*p_line, *pos, i);
	i = -1;
	while (left_overs[++i] && left_overs[i] != '\n')
		line[*pos + i] = left_overs[i];
	*ret = (left_overs[i] == '\n');
	*pos = *pos + i;
	line[*pos] = 0;
	*p_line = line;
	return (i);
}

void	shift_letters(t_list *file, int i)
{
	char	*str;
	int		idx;
	int		size;

	str = file->content;
	size = file->content_size;
	idx = -1;
	while (++idx <= size && str[i + idx])
		str[idx] = str[i + idx];
	while (str[idx] && idx < size)
		str[idx++] = 0;
	if (size >= i)
		file->content_size = size - i;
	else
		file->content_size = 0;
}

t_list	*get_next_file(const int fd, t_list **list)
{
	t_list	*curr;

	curr = *list;
	if (curr == 0)
	{
		curr = ft_lstnew(0, 0);
		*list = curr;
	}
	else
	{
		if (curr->id == fd)
			return (curr);
		while (curr->next)
		{
			if (curr->next->id == fd)
				return (curr->next);
			curr = curr->next;
		}
		curr->next = ft_lstnew(0, 0);
		curr = curr->next;
	}
	curr->id = fd;
	return (curr);
}

int		read_to_next_file(t_list **list)
{
	char	left_overs[BUFF_SIZE];
	t_list	*curr;
	int		ret;

	if (*list == 0)
		return (-1);
	curr = *list;
	if (curr->content_size > 0)
	{
		free(curr->content);
		curr->content = 0;
		curr->content_size = 0;
	}
	ret = read(curr->id, left_overs, BUFF_SIZE);
	if (ret > 0)
	{
		curr->content = ft_strndup(left_overs, ret);
		curr->content_size = ret;
	}
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list = 0;
	t_list			*file;
	int				pos;
	int				ret;

	if (!line || BUFF_SIZE <= 0)
		return (-1);
	*line = ft_strndup("", 0);
	if (*line == 0)
		return (-1);
	pos = 0;
	file = get_next_file(fd, &list);
	while (file->content_size > 0
		|| ((ret = read_to_next_file(&file)) > 0 && ret != -1))
	{
		shift_letters(file,
			copy_until_nline(line, file->content, &pos, &ret) + ret);
		if (ret)
			return (1);
	}
	if (file->content_size > 0)
		((unsigned char*)(file->content))[0] = 0;
	list = 0;
	return (ret < 0 ? -1 : *line[0] != 0);
}
