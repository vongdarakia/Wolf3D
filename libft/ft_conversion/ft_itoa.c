/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 16:36:57 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 16:36:59 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	int		len;
	int		tmp;
	char	*str;

	len = 1;
	tmp = n;
	while (tmp /= 10)
		len++;
	str = (char*)malloc(1 + (n < 0 ? ++len : len));
	if (str && (str[len] = 0) == 0)
	{
		tmp = n < 0 ? -1 : 1;
		if (n < 0)
			str[0] = '-';
		while (--len > 0 && (str[len] = '0' + (n % 10) * tmp))
			n /= 10;
		if (tmp == 1)
			str[0] = '0' + (n % 10) * tmp;
	}
	return (str);
}
