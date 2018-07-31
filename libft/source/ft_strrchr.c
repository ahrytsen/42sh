/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:30:45 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 10:30:48 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int u;

	u = 0;
	if (s)
	{
		while (s[u] != '\0')
			u++;
		while (u != 0)
		{
			if (s[u] == (char)c)
				return ((char*)s + u);
			u--;
		}
		if (s[0] == (char)c)
			return ((char*)s);
	}
	return (NULL);
}
