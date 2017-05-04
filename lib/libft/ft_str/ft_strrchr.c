/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:38:27 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:38:29 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int last_idx;

	i = -1;
	last_idx = -1;
	while (s[++i])
		if (s[i] == c)
			last_idx = i;
	if (s[i] == c)
		return ((char*)(s + i));
	if (last_idx > -1)
		return ((char*)(s + last_idx));
	return (0);
}
