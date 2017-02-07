/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:37:14 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:37:15 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int				i;
	int				len;
	char			*str;

	len = 0;
	while (s1[len])
		len++;
	str = (char*)malloc(sizeof(*str) * (len + 1));
	if (str)
	{
		i = -1;
		while (++i < len)
			str[i] = s1[i];
		str[i] = 0;
		return (str);
	}
	return (0);
}
