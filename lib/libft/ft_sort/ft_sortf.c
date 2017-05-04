/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 16:52:08 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/25 16:52:09 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_sortf(void *arr, size_t n, int (*f)(void *a, void *b))
{
	size_t	i;
	size_t	j;
	int		tmp;

	if (arr && n && f && (i = 0) == 0)
		while (i < n)
		{
			j = 0;
			while (j < n - i - 1)
			{
				if (f(arr + j, arr + j + 1) > 0)
				{
					tmp = ((int*)arr)[j];
					((int*)arr)[j] = ((int*)arr)[j + 1];
					((int*)arr)[j + 1] = tmp;
				}
				j++;
			}
			i++;
		}
}
