/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:14:23 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 15:14:24 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*ptr;
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
			i++;
		ptr = (char*)malloc(sizeof(char) * (i + 1));
		if (!ptr)
			return (NULL);
		i = 0;
		while (s[i])
		{
			ptr[i] = f(s[i]);
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}
