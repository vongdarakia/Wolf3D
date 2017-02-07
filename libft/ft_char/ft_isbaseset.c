/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbaseset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 15:06:24 by avongdar          #+#    #+#             */
/*   Updated: 2016/10/31 15:06:26 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isbaseset(char c, int base)
{
	if (base > 1 && base < 17)
	{
		if (base <= 10 && ft_isdigit(c))
			return (1);
		else if (base > 10 && (ft_isdigit(c)
			|| (c >= 'A' && c <= 'F' && c - 'A' < base - 10)))
			return (1);
	}
	return (0);
}
