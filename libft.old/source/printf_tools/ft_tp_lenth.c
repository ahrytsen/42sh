/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_lenth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:33:54 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/08 11:33:55 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_sg_nbrlen(long long int nbr, int apox)
{
	int i;

	i = 1;
	while (nbr > 9 || nbr < -9)
	{
		nbr /= 10;
		i++;
	}
	if (apox)
		i += (i - 1) / 3;
	return (i);
}

unsigned	ft_un_nbrlen(unsigned long long nbr, unsigned base, int apox)
{
	unsigned i;

	i = 1;
	while (nbr > base - 1)
	{
		nbr /= base;
		i++;
	}
	if (apox && base == 10)
		i += (i - 1) / 3;
	return (i);
}

void		ft_wchar_len(wchar_t *s, int *flags)
{
	int i;
	int k;

	if (!s)
	{
		if (flags[7] == -1 || flags[7] > 6)
			flags[7] = 6;
	}
	else
	{
		i = 0;
		k = 0;
		while (*s)
		{
			k = (*s >= (1 << 7)) + (*s >= (1 << 11)) + (*s >= (1 << 16)) + 1;
			if (i + k <= flags[7] || flags[7] == -1)
				i += k;
			else
				break ;
			s++;
		}
		flags[7] = i;
	}
}

int			ft_strlen_null(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	return (6);
}

int			ft_putlen(char *str, int *flags)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i] && (flags[7] < 0 || i < flags[7]))
			i++;
		write(g_fd, str, i);
		return (i);
	}
	if (flags[7] == -1 || flags[7] > 6)
		return (write(g_fd, "(null)", 6));
	return (write(g_fd, "(null)", flags[7]));
}
