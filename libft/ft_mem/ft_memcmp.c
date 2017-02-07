/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 00:20:28 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 00:20:34 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s_ptr1;
	const unsigned char *s_ptr2;

	s_ptr1 = s1;
	s_ptr2 = s2;
	while (n--)
		if (*s_ptr1 != *s_ptr2)
			return (*s_ptr1 - *s_ptr2);
		else
		{
			s_ptr1++;
			s_ptr2++;
		}
	return (0);
}
