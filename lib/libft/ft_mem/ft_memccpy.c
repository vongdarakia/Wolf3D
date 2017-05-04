/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:50:54 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/22 22:50:55 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	while (n--)
	{
		*(d++) = *(s++);
		if (*(s - 1) == (unsigned char)c)
			return (d);
	}
	return (0);
}
