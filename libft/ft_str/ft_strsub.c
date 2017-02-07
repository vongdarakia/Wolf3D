/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:05:48 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 15:05:49 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		i = 0;
		str = (char*)malloc(len + 1);
		if (str)
		{
			str[len] = 0;
			while (len-- > 0)
				str[i++] = s[start++];
			return (str);
		}
	}
	return (NULL);
}
