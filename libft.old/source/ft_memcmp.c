/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:35:12 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/28 12:35:13 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*a;
	char	*b;

	a = (char*)s1;
	b = (char*)s2;
	if (!a && !b)
		return (0);
	if (!a)
		return (b[0] * -1);
	else if (!b)
		return (a[0]);
	else
	{
		i = 0;
		while ((unsigned char)a[i] == (unsigned char)b[i] && i < n - 1)
			i++;
	}
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}
