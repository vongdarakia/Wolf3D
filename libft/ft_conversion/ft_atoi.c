/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:40:46 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:40:48 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issuperlong(unsigned long long tot, char c)
{
	return ((tot / 922337203685477580U == 1 && (c - '0' >= 8 ||
			tot % 922337203685477580U >= 1)) || tot / 922337203685477580U > 1);
}

int			ft_atoi(const char *str)
{
	int					dir;
	unsigned long long	tot;

	while (ft_isspace(*str))
		str++;
	dir = (*str == '-') ? -1 : 1;
	(tot = 0) == 0 && (*str == '-' || *str == '+') ? str++ : 0;
	while (*str && ft_isdigit(*str))
		if (ft_issuperlong(tot, *str))
			return ((-dir - 1) / 2);
		else
			tot = tot * 10 + (*str++ - '0');
	return (tot * dir);
}
