/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:59:31 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/05 01:59:33 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_leading_zeroes(int len)
{
	while (len-- > 0)
	{
		write(1, "0", 1);
	}
}

void	ft_pfputnbr(intmax_t n, int base, int is_lower)
{
	static char b_lower[] = "0123456789abcdef";
	static char b_upper[] = "0123456789ABCDEF";

	if (base < 2 || base > 16)
		return ;
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0 && n > -base)
		write(1, "-", 1);
	if (n <= -base || n >= base)
		ft_pfputnbr(n / base, base, is_lower);
	if (is_lower)
		write(1, b_lower + (n % base) * (n < 0 ? -1 : 1), 1);
	else
		write(1, b_upper + (n % base) * (n < 0 ? -1 : 1), 1);
}

void	ft_pfputnbr_u(uintmax_t n, unsigned int base, int is_lower)
{
	static char b_lower[] = "0123456789abcdef";
	static char b_upper[] = "0123456789ABCDEF";

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n >= base)
		ft_pfputnbr_u(n / base, base, is_lower);
	if (is_lower)
		write(1, b_lower + (n % base), 1);
	else
		write(1, b_upper + (n % base), 1);
}

int		ft_numlen(intmax_t n, int base)
{
	int len;

	if (base < 2 || base > 16)
		return (0);
	len = 1;
	while (n / base)
	{
		len++;
		n /= base;
	}
	return (len);
}

int		ft_numlen_u(uintmax_t n, unsigned int base, t_env *e)
{
	int len;

	if (base < 2 || base > 16)
		return (0);
	if (n == 0 && e->has_prcsn)
	{
		if (e->spec == 'x' || e->spec == 'X' || e->spec == 'p')
			return (0);
		if (!e->flag_alt_form && e->prcsn_len == 0
			&& (e->spec == 'o' || e->spec == 'O'))
			return (0);
		if (e->prcsn_len == 0 && e->spec == 'u')
			return (0);
	}
	if (n == 0 && e->flag_alt_form && (e->spec == 'o' || e->spec == 'O'))
		return (0);
	len = 1;
	while (n / base)
	{
		len++;
		n /= base;
	}
	return (len);
}
