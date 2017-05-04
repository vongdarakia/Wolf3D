/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:44:57 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/22 16:44:59 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_ptr;

	b_ptr = b;
	while (len--)
		*b_ptr++ = (unsigned char)c;
	return (b);
}
