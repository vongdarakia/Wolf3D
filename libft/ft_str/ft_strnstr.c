/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:57:27 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:57:29 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == *little)
		{
			j = 0;
			while (i + j < len && little[j] && big[j + i]
				&& little[j] == big[j + i])
				j++;
			if (little[j] == 0)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
