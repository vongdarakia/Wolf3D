/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 00:40:43 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/04 00:40:55 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_len_modifier(t_env *e, const char *str)
{
	if (!ft_strequ(e->len_mod, ""))
	{
		if (len_mod_order(e->len_mod) > len_mod_order(str))
		{
			if (ft_strnequ(str, "hh", 2) || ft_strnequ(str, "ll", 2))
				return (2);
			else if (is_len_mod(str))
				return (1);
			return (0);
		}
	}
	if (ft_strnequ(str, "hh", 2))
		e->len_mod = "hh";
	else if (ft_strnequ(str, "ll", 2))
		e->len_mod = "ll";
	else if (*str == 'h' || *str == 'l' || *str == 'j' || *str == 'z')
		e->len_mod = ft_strndup(str, 1);
	return (ft_strlen(e->len_mod));
}

static int	set_specifier(t_env *e, const char *str)
{
	e->spec = *str;
	e->is_specifier_lowercase = (*str >= 'a' && *str <= 'z');
	if (*str == 'D' || *str == 'd' || *str == 'i')
		e->base = 10;
	else if (*str == 'o' || *str == 'O')
		e->base = 8;
	else if (*str == 'x' || *str == 'X')
		e->base = 16;
	else if (*str == 'b' || *str == 'B')
		e->base = 2;
	else if (*str == 'P')
		e->spec = 'p';
	return (1);
}

static void	set_flag(t_env *e, char c)
{
	if (c == '-')
		e->flag_left_just = 1;
	else if (c == '+')
		e->flag_signed = 1;
	else if (c == '0')
		e->flag_leading_zeroes = 1;
	else if (c == ' ')
		e->flag_space = 1;
	else if (c == '#')
		e->flag_alt_form = 1;
}

static int	set_width_and_prscn(t_env *e, const char *str,
	int *after_period, va_list *valist)
{
	int i;

	i = 0;
	if (e->f_width < 0)
	{
		e->f_width *= -1;
		e->flag_left_just = 1;
	}
	if ((str[i] == '.' && ++i >= 0) || (*after_period && str[i] == '*'))
	{
		*after_period = 1;
		e->has_prcsn = 1;
		e->prcsn_len = (str[i] == '*' && ++i >= 0) ?
			va_arg(*valist, int) : ft_atoi((char*)str + i);
		if (e->prcsn_len < 0)
		{
			e->prcsn_len = 0;
			e->has_prcsn = 0;
		}
		while (str[i] && ((str[i] >= '0' && str[i] <= '9')))
			i++;
	}
	return (i);
}

/*
**	Sets the env given a str of where the flags are located.
**	Returns whether or not the flags were valid
*/

int			set_env(t_env *e, const char *str, va_list *valist)
{
	int i;
	int after_period;

	i = 0;
	after_period = 0;
	if (*str == 0)
		return (0);
	while (is_len_mod(str + i) || is_flag(str[i]) || str[i] == '*'
		|| str[i] == '.' || (str[i] >= '0' && str[i] <= '9'))
	{
		while (str[i] && is_flag(str[i]))
			set_flag(e, str[i++]);
		if (str[i] == '*' && (++i >= 0))
			e->f_width = va_arg(*valist, int);
		if (str[i] >= '0' && str[i] <= '9')
			e->f_width = ft_atoi((char*)str + i);
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		i += set_width_and_prscn(e, str + i, &after_period, valist);
		i += set_len_modifier(e, str + i);
	}
	i += set_specifier(e, str + i);
	return (i);
}
