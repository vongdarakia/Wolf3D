/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrbaseset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 15:50:25 by avongdar          #+#    #+#             */
/*   Updated: 2016/10/31 15:50:27 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isstrbaseset(char *str, int base)
{
	if (str && *str)
	{
		while (*str)
			if (!ft_isbaseset(*str++, base))
				return (0);
	}
	else
		return (0);
	return (1);
}
