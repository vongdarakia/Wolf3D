/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 00:04:19 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/26 00:04:20 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double	ft_pow(int base, int pow)
{
	long double total;

	if (pow == 0)
		return (1.0);
	total = 1;
	if (pow > 0)
		while (pow--)
			total *= base;
	else
		while (pow++)
			total /= base;
	return (total);
}
