/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:37:34 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:37:36 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len && (dst[i] = src[i]))
		i++;
	while (i < len)
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}
