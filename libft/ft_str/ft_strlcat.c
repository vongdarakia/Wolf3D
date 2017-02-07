/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:37:59 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:38:00 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static size_t	my_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		dlen;

	d = dst;
	s = src;
	n = size;
	while (*d && n-- != 0)
		d++;
	dlen = d - dst;
	n = size - dlen;
	if (n == 0)
		return (dlen + my_strlen(s));
	while (*s)
	{
		if (n-- != 1)
			*d++ = *s;
		s++;
	}
	*d = 0;
	return (dlen + (s - src));
}
