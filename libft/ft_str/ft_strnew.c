/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 14:04:39 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 14:04:42 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char	*ptr;
	int		i;

	i = size;
	ptr = (char*)malloc(size + 1);
	if (ptr)
	{
		ptr[size] = 0;
		while (size--)
			ptr[size] = 0;
		return (ptr);
	}
	return (NULL);
}
