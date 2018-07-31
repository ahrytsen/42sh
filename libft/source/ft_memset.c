/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:15:46 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/26 18:15:51 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	u;
	size_t			i;
	char			*ptr;

	i = 0;
	u = (unsigned char)c;
	ptr = (char*)b;
	while (i < len)
	{
		ptr[i] = u;
		i++;
	}
	return (b);
}
