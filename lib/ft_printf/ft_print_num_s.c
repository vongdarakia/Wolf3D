/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 02:08:42 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/06 02:08:43 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_num(intmax_t num, t_env *e)
{
	int len;

	len = ft_numlen(num, e->base);
	len -= e->spec == 'd' && num == 0 && e->has_prcsn ? 1 : 0;
	if (num < 0 && num != (long long)(9223372036854775808ull * -1))
		write(1, "-", 1);
	else if (e->flag_signed && num >= 0)
		write(1, "+", 1);
	else if (e->flag_space && num >= 0)
		write(1, " ", 1);
	if (e->has_prcsn)
		ft_put_leading_zeroes(e->prcsn_len - len);
	else if (e->flag_leading_zeroes && e->f_width > len && !e->flag_left_just)
		ft_put_leading_zeroes(e->f_width - len
			- (num < 0 || e->flag_signed || e->flag_space));
	if (num != 0 || (num == 0 && !e->has_prcsn) || (e->has_prcsn
		&& e->prcsn_len > 0 && (e->spec == 'i' || e->spec == 'u')))
		ft_pfputnbr(num < 0 ? num * -1 : num, e->base, e->is_spec_lowercase);
}

void		ft_print_num_signed(t_env *e, va_list *valist)
{
	intmax_t	num;
	int			i;
	int			len;

	i = -1;
	num = 0;
	num = ft_strequ(e->len_mod, "") ? va_arg(*valist, int) : num;
	num = ft_strequ(e->len_mod, "h") ? (short)va_arg(*valist, int) : num;
	num = ft_strequ(e->len_mod, "hh") ? (char)va_arg(*valist, int) : num;
	num = ft_strequ(e->len_mod, "l") ? va_arg(*valist, long) : num;
	num = ft_strequ(e->len_mod, "ll") ? va_arg(*valist, long long) : num;
	num = ft_strequ(e->len_mod, "z") ? va_arg(*valist, ssize_t) : num;
	num = ft_strequ(e->len_mod, "j") ? va_arg(*valist, intmax_t) : num;
	len = ft_numlen(num, e->base);
	len = num == 0 && e->has_prcsn ? 0 : len;
	len = (len > e->prcsn_len ? len : e->prcsn_len)
		+ (num < 0 || e->flag_signed || (e->flag_space && num >= 0));
	if (e->flag_left_just)
		ft_print_num(num, e);
	if (e->has_prcsn || !e->flag_leading_zeroes || e->flag_left_just)
		while (++i < e->f_width - (len))
			write(1, " ", 1);
	if (!e->flag_left_just)
		ft_print_num(num, e);
	e->num_out += e->f_width > len ? e->f_width : len;
}

void		ft_print_num_array(t_env *e, va_list *valist)
{
	int			*num;
	int			i;
	int			len;

	num = va_arg(*valist, int*);
	i = -1;
	len = 0;
	write(1, "[", 1);
	while (++i < e->f_width)
	{
		len += ft_numlen(num[i], e->base);
		ft_pfputnbr(num[i], e->base, e->is_spec_lowercase);
		if (i < e->f_width - 1)
			write(1, ", ", 2);
	}
	write(1, "]", 1);
	len += 2 * (e->f_width > 0 ? e->f_width - 1 : 0);
	e->num_out += len + 2;
}

static void	ft_print_base(intmax_t num, t_env *e)
{
	int len;

	len = ft_numlen(num, e->base);
	len -= e->spec == 'd' && num == 0 && e->has_prcsn ? 1 : 0;
	if (num < 0 && num != (long long)(9223372036854775808ull * -1))
		write(1, "-", 1);
	else if (e->flag_signed && num >= 0)
		write(1, "+", 1);
	else if (e->flag_space && num >= 0)
		write(1, " ", 1);
	if (e->has_prcsn)
		ft_put_leading_zeroes(e->prcsn_len - len);
	if (num != 0 || (num == 0 && !e->has_prcsn) || (e->has_prcsn
		&& e->prcsn_len > 0 && (e->spec == 'i' || e->spec == 'u')))
		ft_pfputnbr(num < 0 ? num * -1 : num, e->base, e->is_spec_lowercase);
}

void		ft_print_num_base(t_env *e, va_list *valist)
{
	intmax_t	num;
	int			i;
	int			len;

	i = -1;
	num = 0;
	num = ft_strequ(e->len_mod, "") ? va_arg(*valist, int) : num;
	num = ft_strequ(e->len_mod, "h") ? (short)va_arg(*valist, int) : num;
	num = ft_strequ(e->len_mod, "hh") ? (char)va_arg(*valist, int) : num;
	num = ft_strequ(e->len_mod, "l") ? va_arg(*valist, long) : num;
	num = ft_strequ(e->len_mod, "ll") ? va_arg(*valist, long long) : num;
	num = ft_strequ(e->len_mod, "z") ? va_arg(*valist, ssize_t) : num;
	num = ft_strequ(e->len_mod, "j") ? va_arg(*valist, intmax_t) : num;
	len = ft_numlen(num, e->base);
	len = num == 0 && e->has_prcsn ? 0 : len;
	len = (len > e->prcsn_len ? len : e->prcsn_len)
		+ (num < 0 || e->flag_signed || (e->flag_space && num >= 0));
	if (e->flag_left_just)
		ft_print_base(num, e);
	if (!e->flag_left_just)
		ft_print_base(num, e);
	e->num_out += len;
}
