/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:32:48 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/14 14:32:50 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static unsigned long long	ft_check_uns(int i, char c, va_list ap)
{
	if (i == 0 && c != 'O' && c != 'U')
		return (va_arg(ap, unsigned));
	if (i == 1 || c == 'O' || c == 'U')
		return (va_arg(ap, unsigned long));
	if (i == 2 && c != 'O' && c != 'U')
		return (va_arg(ap, unsigned long long));
	if (i == 3 && c != 'O' && c != 'U')
		return ((unsigned short)va_arg(ap, int));
	if (i == 4 && c != 'O' && c != 'U')
		return ((unsigned char)va_arg(ap, int));
	if (i == 5 && c != 'O' && c != 'U')
		return (va_arg(ap, uintmax_t));
	if (i == 6 && c != 'O' && c != 'U')
		return (va_arg(ap, size_t));
	return (0);
}

/*
**		OCTAL UNSIGNED INTEGER
*/

int							ft_print_octal(const char **frm,
	va_list ap, int *flags)
{
	int					len;
	unsigned long long	un;

	un = ft_check_uns(flags[8], **frm, ap);
	(*frm)++;
	len = ft_un_nbrlen(un, 8, flags[5]);
	if (len + flags[4] >= flags[7])
		flags[6] -= len + flags[4];
	else
		flags[6] -= flags[7];
	if (un == 0 && ((flags[4] && flags[7] < 2) || (!flags[4] && !flags[7])))
		flags[6]++;
	if (!flags[1] && flags[6] > 0 && (!flags[3] || flags[7] >= 0))
		ft_print_length(flags);
	if (flags[4] && !(un == 0 && (flags[7] == 1 || flags[7] == -1)))
		flags[9] += write(g_fd, "0", 1);
	if (flags[3] && flags[7] < 0 && flags[6] > -1)
	{
		flags[7] = flags[6] + len + flags[4];
		flags[6] = 0;
	}
	ft_put_oct(un, flags);
	if (flags[1] && flags[6] > 0)
		ft_print_length(flags);
	return (flags[9]);
}

/*
**		UNSIGNED INTEGER
*/

int							ft_print_unsigned(const char **frm,
	va_list ap, int *flags)
{
	int					len;
	unsigned long long	un;

	un = ft_check_uns(flags[8], **frm, ap);
	(*frm)++;
	len = ft_un_nbrlen(un, 10, flags[5]);
	if (len >= flags[7])
		flags[6] -= len;
	else
		flags[6] -= flags[7];
	if (un == 0 && flags[7] == 0)
		flags[6]++;
	if (!flags[1] && flags[6] > 0 && (!flags[3] || flags[7] >= 0))
		ft_print_length(flags);
	if (flags[3] && flags[7] < 0 && flags[6] > 0)
	{
		flags[7] = flags[6] + len;
		flags[6] = 0;
	}
	ft_put_un(un, flags, len);
	if (flags[1] && flags[6] > 0)
		ft_print_length(flags);
	return (flags[9]);
}

/*
**		HEX UNSIGNED INTEGER
*/

static void					hex_hlam(char c, int *flags,
	unsigned long long un, int len)
{
	if (c == 'x')
		ft_put_hex(un, "0123456789abcdef", flags, len);
	else
		ft_put_hex(un, "0123456789ABCDEF", flags, len);
	if (flags[1] && flags[6] > 0)
		ft_print_length(flags);
}

int							ft_print_hex(const char **frm,
	va_list ap, int *flags)
{
	int					len;
	unsigned long long	un;

	un = ft_check_uns(flags[8], **frm, ap);
	len = ft_un_nbrlen(un, 16, flags[5]);
	if (len >= flags[7])
		flags[6] -= len + flags[4] * 2;
	else
		flags[6] -= flags[7] + flags[4] * 2;
	if (un == 0 && flags[4])
		flags[6] += 2;
	if (un == 0 && flags[7] == 0)
		flags[6]++;
	if (!flags[1] && flags[6] > 0 && (!flags[3] || flags[7] >= 0))
		ft_print_length(flags);
	if (flags[4] && un != 0)
		flags[9] += write(g_fd, "0", 1) + write(g_fd, &(**frm), 1);
	if (flags[3] && flags[7] < 0 && flags[6] > 0)
	{
		flags[7] = flags[6] + len;
		flags[6] = 0;
	}
	hex_hlam(**frm, flags, un, len);
	(*frm)++;
	return (flags[9]);
}
