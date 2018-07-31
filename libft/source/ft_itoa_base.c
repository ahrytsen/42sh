/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 10:57:42 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/27 10:57:44 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_atata(char *ptr, int n, int d, int base)
{
	char *str;

	str = "0123456789ABCDEF";
	ptr[d] = '\0';
	d--;
	while (n > base - 1 || n < -base + 1)
	{
		if (n >= 0)
			ptr[d] = str[n % base];
		else
			ptr[d] = str[(n % base) * -1];
		n /= base;
		d--;
	}
	if (n >= 0)
		ptr[0] = str[n];
	else
	{
		ptr[1] = str[-n];
		ptr[0] = '-';
	}
	return (ptr);
}

char		*ft_itoa_base(int n, int base)
{
	int		c;
	int		d;
	char	*ptr;

	c = n;
	d = 0;
	while (c > base - 1 || c < -base + 1)
	{
		d++;
		c /= base;
	}
	if (c < 0)
		d++;
	d++;
	ptr = (char *)malloc(sizeof(char) * (d + 1));
	ptr = ft_atata(ptr, n, d, base);
	return (ptr);
}
