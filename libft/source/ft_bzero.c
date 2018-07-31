/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 19:27:59 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/26 19:28:01 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = (char*)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
