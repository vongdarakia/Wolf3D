/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 13:38:12 by avongdar          #+#    #+#             */
/*   Updated: 2016/10/31 13:38:14 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issuperlong(unsigned long long tot, char c)
{
	return ((tot / 922337203685477580U == 1 && (c - '0' >= 8 ||
			tot % 922337203685477580U >= 1)) || tot / 922337203685477580U > 1);
}

int			ft_atoi_base(const char *str, int base)
{
	int					dir;
	unsigned long long	tot;

	if (base < 2 || base > 16)
		return (0);
	while (ft_isspace(*str))
		str++;
	dir = (*str == '-') ? -1 : 1;
	tot = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isbaseset(*str, base))
		if (ft_issuperlong(tot, *str))
			return ((-dir - 1) / 2);
		else if (ft_isdigit(*str))
			tot = tot * base + (*str++ - '0');
		else
			tot = tot * base + (*str++ - 'A' + 10);
	return (tot * dir);
}
