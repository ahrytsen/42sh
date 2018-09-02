/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 03:07:22 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/26 17:23:59 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, int n)
{
	while (n-- && *s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	if (*s == (char)c && n >= 0)
		return ((char*)s);
	return (NULL);
}
