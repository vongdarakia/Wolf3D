/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 23:35:30 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 23:36:21 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;
	size_t sz;

	new = (t_list*)malloc(sizeof(t_list));
	if (new)
	{
		if (content)
		{
			sz = content_size;
			new->content_size = content_size;
			new->content = (char*)malloc(content_size);
			while (sz--)
				((char*)new->content)[sz] = ((char*)content)[sz];
		}
		else
		{
			new->content = 0;
			new->content_size = 0;
		}
		new->next = 0;
		return (new);
	}
	return (0);
}
