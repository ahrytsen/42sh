/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:10:54 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 12:10:55 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *ptr;

	if (!size)
		return (NULL);
	ptr = (char*)malloc(size + 1);
	if (!ptr)
		return (NULL);
	while (size > 0)
	{
		ptr[size] = '\0';
		size--;
	}
	ptr[0] = '\0';
	return (ptr);
}
