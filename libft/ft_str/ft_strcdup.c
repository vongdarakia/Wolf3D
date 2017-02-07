/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:13:14 by avongdar          #+#    #+#             */
/*   Updated: 2016/10/10 13:13:16 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcdup(const char *str, unsigned char c)
{
	char	*new;
	int		i;
	int		len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	new = (char*)malloc(len + 1);
	if (new)
	{
		i = -1;
		while (str[++i] && len--)
			new[i] = str[i];
		new[i] = 0;
		return (new);
	}
	return (0);
}
