/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:25:13 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/08 11:25:16 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <unistd.h>
#include <stdlib.h>

/*
**		PRINT INTEGER/STRINGS
*/

void			ft_put_oct(unsigned long long n, int *flags)
{
	char c;

	if (n == 0 && flags[7] == 0)
		return ;
	if (n > 7)
	{
		flags[9]++;
		flags[7]--;
		ft_put_oct(n / 8, flags);
		c = n % 8 + 48;
		write(g_fd, &c, 1);
	}
	else
	{
		while (flags[7] - flags[4] > 1)
		{
			write(g_fd, "0", 1);
			flags[7]--;
			flags[9]++;
		}
		c = ((n << 61) >> 61) + 48;
		write(g_fd, &c, 1);
		flags[9]++;
	}
}

void			ft_put_hex(unsigned long long n, char *str, int *flags, int len)
{
	char	*ptr;
	int		i;

	if (n == 0 && flags[7] == 0)
		return ;
	if (flags[7] > len)
		len = flags[7];
	ptr = (char *)malloc(sizeof(char) * len);
	i = len;
	len--;
	while (len)
	{
		ptr[len] = str[n % 16];
		n /= 16;
		len--;
	}
	ptr[len] = str[n];
	flags[9] += write(g_fd, ptr, i);
	free(ptr);
}

static void		ft_it_ll_base(char *ptr, unsigned long long n,
	int len, int *flags)
{
	char	*str;
	int		i;

	i = 0;
	str = "0123456789";
	len--;
	while (len)
	{
		if (flags[5] && i % 3 == 0 && i != 0 && n > 0)
		{
			ptr[len] = ',';
			len--;
		}
		ptr[len] = str[n % 10];
		n /= 10;
		i++;
		len--;
	}
	ptr[len] = str[n];
}

void			ft_put_un(unsigned long long n, int *flags, int len)
{
	char	*ptr;

	if (n == 0 && flags[7] == 0)
		return ;
	if (flags[7] > len)
		len = flags[7];
	ptr = (char *)malloc(sizeof(char) * len);
	ft_it_ll_base(ptr, n, len, flags);
	flags[9] += write(g_fd, ptr, len);
	free(ptr);
}

void			ft_put_sg(long long int n, int *flags, int len)
{
	char				*ptr;
	unsigned long long	un;

	if (n == 0 && flags[7] == 0)
		return ;
	if (n < 0)
		un = -n;
	else
		un = n;
	if (flags[7] > len)
		len = flags[7];
	ptr = (char *)malloc(sizeof(char) * len);
	ft_it_ll_base(ptr, un, len, flags);
	flags[9] += write(g_fd, ptr, len);
	free(ptr);
}
