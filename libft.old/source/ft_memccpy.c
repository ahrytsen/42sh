/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:16:01 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/28 10:16:02 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ds;
	unsigned char	*sr;
	size_t			i;

	ds = (unsigned char*)dst;
	sr = (unsigned char*)src;
	i = 0;
	if (n && ds != sr && ds && sr)
	{
		while (i < n && *sr != (unsigned char)c)
		{
			*ds++ = *sr++;
			i++;
		}
	}
	if (i < n)
	{
		*ds++ = *sr++;
		return ((void*)ds);
	}
	return (NULL);
}
