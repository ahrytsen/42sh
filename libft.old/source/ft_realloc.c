/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 11:47:22 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/26 11:47:24 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(size_t new_size, size_t old_size, char *ptr)
{
	char	*tmp;

	if (new_size <= old_size)
		return (ptr);
	if (!ptr)
		return (ft_memalloc(new_size + 1));
	if (!(tmp = (char *)malloc(sizeof(char) * (new_size + 1))))
		return (NULL);
	while (old_size)
	{
		tmp[old_size] = ptr[old_size];
		old_size--;
	}
	tmp[old_size] = ptr[old_size];
	free(ptr);
	return (tmp);
}
