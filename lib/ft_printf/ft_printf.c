/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 21:36:45 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/03 21:36:46 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_env(t_env *e)
{
	e->flag_left_just = 0;
	e->flag_signed = 0;
	e->flag_leading_zeroes = 0;
	e->flag_space = 0;
	e->flag_alt_form = 0;
	e->f_width = 0;
	e->has_prcsn = 0;
	e->prcsn_len = 0;
	e->len_mod = "";
	e->spec = 0;
	e->num_out = 0;
	e->base = 10;
	e->is_spec_lowercase = 1;
}

static void	clear_env(t_env *e)
{
	e->flag_left_just = 0;
	e->flag_signed = 0;
	e->flag_leading_zeroes = 0;
	e->flag_space = 0;
	e->flag_alt_form = 0;
	e->f_width = 0;
	e->has_prcsn = 0;
	e->prcsn_len = 0;
	e->len_mod = "";
	e->spec = 0;
	e->base = 10;
	e->is_spec_lowercase = 1;
}

int			ft_printf(const char *str, ...)
{
	va_list			valist;
	t_env			e;
	int				i;

	i = -1;
	va_start(valist, str);
	init_env(&e);
	while (str[++i])
		if (str[i] == '%')
		{
			i += set_env(&e, str + i + 1, &valist);
			if (e.spec != 0)
				call_func(&e, &valist);
			else if (str[i] != '%')
				i--;
			clear_env(&e);
		}
		else if (e.num_out++ >= 0)
			write(1, str + i, 1);
	va_end(valist);
	return (e.num_out);
}
