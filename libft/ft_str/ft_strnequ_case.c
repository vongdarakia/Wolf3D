/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 23:05:32 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/25 23:05:38 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strnequ_case(char const *s1, char const *s2, size_t n, int is_sen)
{
	if (s1 && s2 && n)
	{
		while (*s1 && *s2 && n--)
		{
			if (is_sen && *s1 != *s2)
				return (0);
			else if (!is_sen && ft_toupper(*s1) != ft_toupper(*s2))
				return (0);
			s1++;
			s2++;
		}
		if (*s1 == *s2)
			return (1);
		else if (!is_sen && ft_toupper(*s1) != ft_toupper(*s2))
			return (1);
		if ((int)n != -1)
			return (0);
	}
	else if (s1 != s2 && n)
		return (0);
	return (1);
}
