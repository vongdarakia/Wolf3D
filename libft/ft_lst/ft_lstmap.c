/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 00:17:15 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/24 00:17:16 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *cur;

	if (lst)
	{
		new = (t_list*)malloc(sizeof(t_list));
		new = f(lst);
		cur = new;
		lst = lst->next;
		while (lst)
		{
			cur->next = f(lst);
			cur = cur->next;
			lst = lst->next;
		}
		return (new);
	}
	return (0);
}
