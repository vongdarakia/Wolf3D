/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 00:03:29 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/24 00:03:31 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (alst && *alst)
	{
		if ((*alst)->next)
			ft_lstdel(&((*alst)->next), del);
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = 0;
	}
}
