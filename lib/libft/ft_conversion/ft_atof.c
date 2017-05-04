/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 19:26:59 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/25 19:27:02 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	ft_inf(int sign)
{
	int inf;

	inf = 0x7F800000;
	return (sign * *(float*)&inf);
}

static float	ft_nan(void)
{
	int nan;

	nan = 0x7F800001;
	return (*(float*)&nan);
}

double			ft_atof(const char *s)
{
	long double	dir;
	long double	tot;
	double		pt;

	tot = 0.0;
	if ((dir = 1) && !s)
		return (0.0);
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		dir = 44 - *s++;
	if (*s == '.' && !ft_isdigit(*(s + 1)))
		dir = 1;
	if (*s != 0 && ft_strnequ_case(s, "INF", 3, 0))
		return (ft_inf(dir));
	if (*s != 0 && ft_strnequ_case(s, "NAN", 3, 0))
		return (ft_nan());
	while (*s && ft_isdigit(*s))
		tot = tot * 10.0f + (*s++ - '0');
	if (*s == '.' && (pt = 1.0) && *s++)
		while (*s && ft_isdigit(*s))
			tot += (*s++ - '0') * (pt /= 10.0f);
	if (*s++ == 'e' && (ft_isdigit(*s) || *s == '-' || *s == '+'))
		return (tot * dir * ft_pow(10, ft_atoi(s)));
	return (tot * dir);
}
