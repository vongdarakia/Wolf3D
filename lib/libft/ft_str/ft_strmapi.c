/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 14:34:09 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 14:34:10 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*str;

	len = 0;
	if (s && f)
	{
		while (s[len])
			len++;
		str = (char*)malloc(sizeof(char) * len + 1);
		if (str)
		{
			str[len] = 0;
			len = -1;
			while (s[++len])
				str[len] = f(len, s[len]);
			return (str);
		}
	}
	return (0);
}
