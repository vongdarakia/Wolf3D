/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:19:36 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/29 15:22:12 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrealloc(char *n_buff, int len, int additional)
{
	char	*new_str;

	new_str = (char*)malloc(sizeof(char) * (len + additional + 1));
	if (!new_str)
		return (0);
	if (n_buff)
	{
		ft_strncpy(new_str, n_buff, len);
		free(n_buff);
	}
	return (new_str);
}
