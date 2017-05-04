/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 21:30:26 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 21:30:27 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	free_everything(char ***split, int wc)
{
	while (wc--)
		free((*split)[wc]);
	free(*split);
	*split = 0;
}

static void	do_split(char const *s, char c, char ***split)
{
	int wc;
	int i;
	int j;
	int len;

	wc = 0;
	i = -1;
	len = 0;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c) && (j = -1))
		{
			(*split)[wc] = (char*)malloc(++len + 1);
			if (!((*split)[wc]))
			{
				free_everything(split, wc);
				return ;
			}
			while (++j < len)
				(*split)[wc][j] = s[i + 1 - len + j];
			(*split)[wc++][j] = 0;
			len = 0;
		}
		else if (s[i] != c)
			len++;
	(*split)[wc] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		wc;
	int		len;
	char	**split;

	i = -1;
	wc = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[++i])
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			wc++;
	split = (char**)malloc(sizeof(char*) * (wc + 1));
	if (split)
	{
		split[wc] = 0;
		do_split(s, c, &split);
	}
	return (split);
}
