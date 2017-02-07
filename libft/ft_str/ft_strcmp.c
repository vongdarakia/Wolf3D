/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:39:05 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:39:07 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int l;

	l = 0;
	while (s1[l] && s1[l] == s2[l])
		l++;
	return ((unsigned char)s1[l] - (unsigned char)s2[l]);
}
