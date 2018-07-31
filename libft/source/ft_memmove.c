/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 10:18:27 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/28 10:18:28 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*ds;
	const char	*sr;
	char		*tmp;
	size_t		i;

	ds = dst;
	sr = src;
	i = 0;
	tmp = (char*)malloc(n);
	if (n && tmp && sr)
	{
		while (i < n)
		{
			tmp[i] = sr[i];
			i++;
		}
	}
	while (n)
	{
		ds[n - 1] = tmp[n - 1];
		n--;
	}
	free(tmp);
	return (dst);
}
