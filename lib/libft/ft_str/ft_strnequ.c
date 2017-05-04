/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:05:41 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 15:05:42 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2 && n)
	{
		while (*s1 && *s2 && n--)
			if (*s1++ != *s2++)
				return (0);
		if (n == 0 || *s1 == *s2)
			return (1);
		if ((int)n != -1)
			return (0);
	}
	else if (s1 != s2 && n)
		return (0);
	return (1);
}
