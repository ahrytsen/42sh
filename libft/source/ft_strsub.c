/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:05:54 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 18:05:55 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s)
	{
		i = 0;
		ptr = (char*)malloc(sizeof(char) * (len + 1));
		if (!ptr)
			return (NULL);
		while (i < len && s[start + i])
		{
			ptr[i] = s[start + i];
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}
