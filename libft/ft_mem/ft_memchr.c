/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 00:09:47 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 00:09:48 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *s_ptr;

	s_ptr = (unsigned char*)s;
	while (n--)
	{
		if (*s_ptr == (unsigned char)c)
			return (s_ptr);
		s_ptr++;
	}
	return (0);
}
