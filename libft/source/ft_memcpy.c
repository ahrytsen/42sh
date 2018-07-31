/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:15:17 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/28 10:15:18 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ds;
	const char	*sr;
	size_t		i;

	ds = dst;
	sr = src;
	i = 0;
	if (n && ds != sr && ds && sr)
	{
		while (i < n)
		{
			ds[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
