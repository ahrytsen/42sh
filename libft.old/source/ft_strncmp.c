/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:54:23 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/26 14:54:24 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if ((!s1 && !s2) || n == 0)
		return (0);
	if (!s1)
		return (s2[0] * -1);
	else if (!s2)
		return (s1[0]);
	else
	{
		i = 0;
		while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& (s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
			i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
