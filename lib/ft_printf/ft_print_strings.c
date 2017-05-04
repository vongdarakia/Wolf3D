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

static char	get_wide_char_len(wchar_t c)
{
	if (c < 0xFF)
		return (1);
	else if (c < 0x800)
		return (2);
	else if (c < 0x10000)
		return (3);
	else if (c < 0x200000)
		return (4);
	return (0);
}

/*
**	0x3F is 111111 in binary. We '&' with this to mode for the right bits.
**	'0x80 |' is just adding 128 to the number we extracted from the bits.
**	please read source for more info.
**	src: https://en.wikipedia.org/wiki/UTF-8
**		Diagram: FSS-UTF (1992) / UTF-8 (1993)
*/

static char	*ft_wchar_to_str(wchar_t c)
{
	int		len;
	char	*str;
	int		i;

	len = get_wide_char_len(c);
	i = -1;
	if (c < 0 || (c >= 0xD800 && c <= 0xDFFF) || c > 0x10FFFF)
		return ("");
	if (len == 0)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	str[len] = 0;
	str[0] = (char)c;
	if (len == 1)
		return (str);
	i = -1;
	while (++i < len)
		str[i] = 0x80 | ((c >> (6 * (len - i - 1))) & 0x3F);
	str[0] |= 0x80 - (1 << (8 - len));
	return (str);
}

static char	*ft_wstr_to_str(wchar_t *s, t_env *e)
{
	int		i;
	int		j;
	int		len;
	char	*str;
	char	*new_str;

	if (!s)
		return (0);
	i = -1;
	str = (char*)malloc(sizeof(char) * 1);
	str[0] = 0;
	while (s[++i] && (len = ft_strlen(str)) >= 0)
		if (!e->has_prcsn ||
			(e->has_prcsn && len + get_wide_char_len(s[i]) <= e->prcsn_len))
		{
			str = ft_strrealloc(str, len, get_wide_char_len(s[i]));
			new_str = ft_wchar_to_str(s[i]);
			j = ft_strlen(new_str);
			str[len + j] = 0;
			while (--j >= 0)
				str[len + j] = new_str[j];
		}
	return (str);
}

static char	*get_str(t_env *e, va_list *valist)
{
	char *str;

	if (e->spec == 'C')
		str = ft_wchar_to_str(va_arg(*valist, wchar_t));
	else if (e->spec == 'S')
		str = ft_wstr_to_str(va_arg(*valist, wchar_t*), e);
	else
		str = va_arg(*valist, char*);
	return (str);
}

void		ft_print_s(t_env *e, va_list *valist)
{
	char	*str;
	int		i;
	int		len;

	str = get_str(e, valist);
	str = str == 0 ? "(null)" : str;
	len = e->spec == 'C' && *str == 0 ? 1 : ft_strlen(str);
	if ((i = -1) && e->has_prcsn && e->spec != 'C')
		len = e->prcsn_len >= len ? len : e->prcsn_len;
	if (e->flag_left_just)
		write(1, str, len);
	while (++i < e->f_width - len)
		if (e->flag_leading_zeroes && !e->flag_left_just)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	if (!e->flag_left_just)
		write(1, str, len);
	e->num_out += e->f_width > len ? e->f_width : len;
}
