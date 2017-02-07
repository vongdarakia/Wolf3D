/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:39:15 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:39:16 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t l;

	l = 0;
	while (s1[l] && s1[l] == s2[l] && l < n)
		l++;
	if (l == n)
		return (0);
	return ((unsigned char)s1[l] - (unsigned char)s2[l]);
}
