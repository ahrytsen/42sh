/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:10:20 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/26 15:10:22 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	dup = (char *)malloc(sizeof(*dup) * (i + 1));
	if (!dup)
		return (NULL);
	while (i > -1)
	{
		dup[i] = s1[i];
		i--;
	}
	return (dup);
}
