/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:47:39 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/21 13:47:41 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (big[i])
	{
		if (big[i] == *little)
		{
			j = 0;
			while (little[j] && big[j + i] && little[j] == big[j + i])
				j++;
			if (little[j] == 0)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
