/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:22:11 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 17:22:12 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	if ((!s1 && !s2) || n == 0)
		return (1);
	else if (!s1 || !s2)
		return (0);
	else
	{
		i = 0;
		while ((unsigned char)s1[i] == (unsigned char)s2[i]
			&& (s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
			i++;
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (0);
	}
	return (1);
}
