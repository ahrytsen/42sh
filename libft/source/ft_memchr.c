/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:35:05 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/28 12:35:06 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;

	if (s)
	{
		tmp = (unsigned char*)s;
		while (n)
		{
			if (*tmp == (unsigned char)c)
				return ((void*)tmp);
			tmp++;
			n--;
		}
	}
	return (NULL);
}
