/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:25:53 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/30 11:25:55 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *ptr;

	if (!size)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	while (size > 0)
	{
		ptr[size - 1] = 0;
		size--;
	}
	return (ptr);
}
