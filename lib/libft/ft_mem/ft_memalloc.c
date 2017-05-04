/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 10:09:05 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 10:09:07 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	char	*ptr;

	ptr = (char*)malloc(size);
	if (ptr)
	{
		while (size--)
			ptr[size] = 0;
		return (ptr);
	}
	return (NULL);
}
