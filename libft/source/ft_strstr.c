/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:32:28 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 10:32:29 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	const char *ptr;
	const char *dck;

	if (*little == '\0' && big)
		return ((char*)big);
	while (*big)
	{
		if (*big == *little)
		{
			dck = big;
			ptr = little;
			while (*dck == *ptr && *dck)
			{
				dck++;
				ptr++;
			}
			if (*ptr == '\0')
				return ((char*)big);
		}
		big++;
	}
	return (NULL);
}
