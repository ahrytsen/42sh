/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:21:08 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 18:21:09 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1;
	ptr = (char*)malloc(len);
	if (!ptr)
		return (NULL);
	tmp = ptr;
	if (s1)
		while (*s1 && (*ptr = *s1))
		{
			ptr++;
			s1++;
		}
	if (s2)
		while (*s2 && (*ptr = *s2))
		{
			ptr++;
			s2++;
		}
	*ptr = '\0';
	return (tmp);
}
