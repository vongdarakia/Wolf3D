/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 02:08:42 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/06 02:08:43 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_alt_form(t_env *e, uintmax_t num)
{
	if (e->flag_alt_form)
	{
		if (num == 0 && e->spec != 'p' && (e->spec == 'x' || e->spec == 'X'))
			return ;
		if ((e->spec == 'o' || e->spec == 'O'))
			write(1, "0", 1);
		else if ((num != 0) || e->spec == 'p')
		{
			if (e->spec == 'x' || e->spec == 'p')
				write(1, "0x", 2);
			else if (e->spec == 'X')
				write(1, "0X", 2);
		}
	}
}

static int	len_alt_form(t_env *e, uintmax_t num)
{
	if (e->flag_alt_form)
	{
		if (num != 0 && (e->spec == 'x' || e->spec == 'X'))
			return (2);
		else if ((e->spec == 'o' || e->spec == 'O'))
			return (1);
		else if (e->spec == 'p')
			return (2);
	}
	return (0);
}

static void	ft_print_num_u(uintmax_t num, t_env *e)
{
	int len;

	len = ft_numlen_u(num, e->base, e) + len_alt_form(e, num);
	print_alt_form(e, num);
	if (e->has_prcsn && (e->spec == 'p' || e->spec == 'x' || e->spec == 'X'))
		ft_put_leading_zeroes(e->prcsn_len - len + len_alt_form(e, num));
	else if (e->has_prcsn)
		ft_put_leading_zeroes(e->prcsn_len - len);
	else if (e->flag_leading_zeroes && e->f_width > len && !e->flag_left_just)
		ft_put_leading_zeroes(e->f_width - len);
	if (ft_numlen_u(num, e->base, e) > 0)
		ft_pfputnbr_u(num, e->base, e->is_spec_lowercase);
}

static int	len_with_precision(uintmax_t num, t_env *e)
{
	int len;

	len = ft_numlen_u(num, e->base, e) + len_alt_form(e, num);
	if ((e->spec == 'p' || e->spec == 'x' || e->spec == 'X') && e->has_prcsn)
	{
		if (num == 0)
			len += e->prcsn_len;
		else if (e->prcsn_len > ft_numlen_u(num, e->base, e))
			len += e->prcsn_len - ft_numlen_u(num, e->base, e);
	}
	else
		len = (e->prcsn_len > len ? e->prcsn_len : len);
	return (len);
}

void		ft_print_num_unsigned(t_env *e, va_list *valist)
{
	uintmax_t	num;
	int			i;
	int			len;

	i = -1;
	num = 0;
	num = ft_strequ(e->len_mod, "") ? va_arg(*valist, USI) : num;
	num = ft_strequ(e->len_mod, "h") ? (USS)va_arg(*valist, USI) : num;
	num = ft_strequ(e->len_mod, "hh") ? (USC)va_arg(*valist, USI) : num;
	num = ft_strequ(e->len_mod, "l") ? va_arg(*valist, USL) : num;
	num = ft_strequ(e->len_mod, "ll") ? va_arg(*valist, USLL) : num;
	num = ft_strequ(e->len_mod, "z") ? va_arg(*valist, size_t) : num;
	num = ft_strequ(e->len_mod, "j") ? va_arg(*valist, uintmax_t) : num;
	len = len_with_precision(num, e);
	if (e->flag_left_just)
		ft_print_num_u(num, e);
	if (e->has_prcsn || !e->flag_leading_zeroes || e->flag_left_just)
		while (++i + len < e->f_width)
			write(1, " ", 1);
	if (!e->flag_left_just)
		ft_print_num_u(num, e);
	e->num_out += (e->f_width > len ? e->f_width : len);
}
