/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:33:13 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 10:33:15 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char *ptr;
	const char *dck;

	if (*little == '\0' && big)
		return ((char*)big);
	while (*big && len)
	{
		if (*big == *little)
		{
			dck = big;
			ptr = little;
			while (*dck == *ptr && len && *dck)
			{
				dck++;
				ptr++;
				len--;
			}
			if (*ptr == '\0')
				return ((char*)big);
		}
		big++;
		if (len)
			len--;
	}
	return (NULL);
}
