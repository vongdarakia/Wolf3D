/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 02:09:57 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/06 02:09:58 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_c(t_env *e, va_list *valist)
{
	char	c;
	int		i;

	i = -1;
	c = e->spec == 'c' ? va_arg(*valist, int) : e->spec;
	if (e->flag_left_just)
		write(1, &c, 1);
	while (++i < e->f_width - 1)
		if (e->flag_leading_zeroes && !e->flag_left_just)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	if (!e->flag_left_just)
		write(1, &c, 1);
	if (e->spec != 0)
		e->num_out += (e->f_width > 1 ? e->f_width : 1);
}
