/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 20:02:05 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/05 20:02:06 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				alt_preset(t_env *e)
{
	if (e->spec == 'U' || e->spec == 'O')
		e->len_mod = "ll";
	if (e->spec == 'D')
		e->len_mod = "l";
	if (e->spec == 'B')
		e->len_mod = "ll";
	if (e->spec == 'm')
		e->base = e->f_width;
	if (e->spec == 'p')
	{
		e->flag_alt_form = 1;
		e->len_mod = "l";
		e->base = 16;
	}
	e->spec = (e->spec == 'c' && ft_strequ(e->len_mod, "l")) ? 'C' : e->spec;
	e->spec = (e->spec == 's' && ft_strequ(e->len_mod, "l")) ? 'S' : e->spec;
}

void					call_func(t_env *e, va_list *valist)
{
	alt_preset(e);
	if (e->spec == 'C' || e->spec == 's' || e->spec == 'S')
		ft_print_s(e, valist);
	else if (e->spec == 'i' || e->spec == 'd' || e->spec == 'D')
		ft_print_num_signed(e, valist);
	else if (e->spec == 'x' || e->spec == 'X'
		|| e->spec == 'o' || e->spec == 'O' || e->spec == 'u' || e->spec == 'U'
		|| e->spec == 'p' || e->spec == 'P' || e->spec == 'b' || e->spec == 'B')
		ft_print_num_unsigned(e, valist);
	else if (e->spec == 'a')
		ft_print_num_array(e, valist);
	else if (e->spec == 'm')
		ft_print_num_base(e, valist);
	else
		ft_print_c(e, valist);
}
