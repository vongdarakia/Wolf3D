/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:06:00 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 15:06:01 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	str = (char*)malloc(i + j + 1);
	if (str)
	{
		str[i + j] = 0;
		i = -1;
		while (s1 && s1[++i])
			str[i] = s1[i];
		j = -1;
		while (s2 && s2[++j])
			str[i + j] = s2[j];
		return (str);
	}
	return (NULL);
}
