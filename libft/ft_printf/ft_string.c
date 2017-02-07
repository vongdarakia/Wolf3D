/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 02:01:22 by avongdar          #+#    #+#             */
/*   Updated: 2016/12/04 02:01:23 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		while (*s1 && *s2)
			if (*s1++ != *s2++)
				return (0);
		if (*s1 != *s2)
			return (0);
	}
	else if (s1 != s2)
		return (0);
	return (1);
}

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2 && n)
	{
		while (*s1 && *s2 && n--)
			if (*s1++ != *s2++)
				return (0);
		if (n == 0 || *s1 == *s2)
			return (1);
		if ((int)n != -1)
			return (0);
	}
	else if (s1 != s2 && n)
		return (0);
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

char	*ft_strndup(const char *str, int n)
{
	char	*new;
	int		i;

	new = (char*)malloc(n + 1);
	if (new)
	{
		i = -1;
		while (str[++i] && n--)
			new[i] = str[i];
		new[i] = 0;
		return (new);
	}
	return (0);
}

char	*ft_strrealloc(char *n_buff, int len, int additional)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char*)malloc(sizeof(char) * (len + additional + 1));
	if (!new_str)
		return (0);
	if (n_buff)
	{
		while (i < len && (new_str[i] = n_buff[i]))
			i++;
		while (i < len)
		{
			new_str[i] = 0;
			i++;
		}
		free(n_buff);
	}
	return (new_str);
}
