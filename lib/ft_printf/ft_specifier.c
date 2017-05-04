/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 06:32:06 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/22 06:32:08 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_signed(char spec)
{
	return (spec == 'd' || spec == 'i');
}

int	is_unsigned(char spec)
{
	return (spec == 'D' || spec == 'u' || spec == 'U'
		|| spec == 'o' || spec == 'O'
		|| spec == 'x' || spec == 'X');
}

int	is_flag(char spec)
{
	return (spec == '-' || spec == '+' || spec == '0'
		|| spec == ' ' || spec == '#');
}

int	is_len_mod(const char *str)
{
	if (ft_strnequ(str, "hh", 2) || ft_strnequ(str, "ll", 2))
		return (1);
	else if (*str == 'h' || *str == 'l' || *str == 'j' || *str == 'z')
		return (1);
	return (0);
}

int	len_mod_order(const char *mod)
{
	if (*mod == 0)
		return (0);
	if (ft_strnequ(mod, "hh", 2))
		return (1);
	if (ft_strnequ(mod, "h", 1))
		return (2);
	if (ft_strnequ(mod, "l", 1))
		return (3);
	if (ft_strnequ(mod, "ll", 2))
		return (4);
	if (ft_strnequ(mod, "j", 1))
		return (5);
	if (ft_strnequ(mod, "z", 1))
		return (6);
	if (ft_strnequ(mod, "t", 1))
		return (7);
	return (0);
}
