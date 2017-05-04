/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 16:27:24 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 16:27:25 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int		len;
	int		i;
	char	*str;
	int		ws;

	len = 0;
	i = -1;
	ws = 0;
	while (s && s[++i])
		if ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && ++ws)
			len > 0 ? len++ : 0;
		else if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t' && ++len)
			ws = 0;
	len = (len - ws < 0 ? 0 : len - ws);
	str = (char*)malloc(len + 1);
	if (!str || !s)
		return (NULL);
	str[len] = 0;
	while (len > 0 && s[--i])
		if (ws > 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			ws--;
		else
			str[--len] = s[i];
	return (str);
}
