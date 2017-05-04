/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 16:31:13 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/25 16:31:22 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strndup(const char *str, int n)
{
	char	*new;
	int		i;

	new = (char*)malloc(n + 1);
	if (new)
	{
		i = -1;
		while (str[++i] && n--)
			new[i] = str[i];
		new[i] = 0;
		return (new);
	}
	return (0);
}
