/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:42:31 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/14 14:42:33 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**		PRINT SIGNED INTEGER
*/

static long long	ft_check_dec(int i, char c, va_list ap)
{
	if (i == 0 && c != 'D')
		return (va_arg(ap, int));
	if (i == 1 || c == 'D')
		return (va_arg(ap, long int));
	if (i == 2 && c != 'D')
		return (va_arg(ap, long long int));
	if (i == 3 && c != 'D')
		return ((short)va_arg(ap, int));
	if (i == 4 && c != 'D')
		return ((char)va_arg(ap, int));
	if (i == 5 && c != 'D')
		return (va_arg(ap, intmax_t));
	if (i == 6 && c != 'D')
		return (va_arg(ap, size_t));
	return (0);
}

static void			signed_hlam(long long dec, int len, int *flags)
{
	if (len >= flags[7])
		flags[6] -= len;
	else
		flags[6] -= flags[7];
	if (((flags[0] || flags[2]) && dec >= 0) || dec < 0)
		flags[6]--;
	if (dec == 0 && flags[7] == 0)
		flags[6]++;
	if (!flags[1] && flags[6] > 0 && (!flags[3] || flags[7] >= 0))
		ft_print_length(flags);
	if ((flags[0] || flags[2]) && dec >= 0)
		flags[9] += write(g_fd, "+", flags[0]) + write(g_fd, " ", flags[2]);
	if (dec < 0)
		flags[9] += write(g_fd, "-", 1);
	if (flags[3] && flags[7] < 0 && flags[6] > 0)
	{
		flags[7] = flags[6] + len;
		flags[6] = 0;
	}
	ft_put_sg(dec, flags, len);
	if (flags[1] && flags[6] > 0)
		ft_print_length(flags);
}

int					ft_print_signed(const char **frm, va_list ap, int *flags)
{
	long long	dec;
	int			len;

	dec = ft_check_dec(flags[8], **frm, ap);
	(*frm)++;
	len = ft_sg_nbrlen(dec, flags[5]);
	signed_hlam(dec, len, flags);
	return (flags[9]);
}

/*
**		PRINT POINTERS
*/

int					ft_print_ptr(const char **frm, va_list ap, int *flags)
{
	unsigned long	un;
	int				len;

	un = va_arg(ap, unsigned long);
	len = ft_un_nbrlen(un, 16, flags[5]);
	if (len >= flags[7])
		flags[6] -= len + 2;
	else
		flags[6] -= flags[7] + 2;
	if (un == 0 && flags[7] == 0)
		flags[6]++;
	if (!flags[1] && flags[6] > 0 && (!flags[3] || flags[7] >= 0))
		ft_print_length(flags);
	write(g_fd, "0x", 2);
	if (flags[3] && flags[7] < 0 && flags[6] > 0)
	{
		flags[7] = flags[6] + len;
		flags[6] = 0;
	}
	ft_put_hex(un, "0123456789abcdef", flags, len);
	if (flags[1] && flags[6] > 0)
		ft_print_length(flags);
	(*frm)++;
	return (flags[9] + 2);
}

/*
**		SEARCH SOME $$
*/

int					ft_search_dollar(const char **frm, va_list cp, va_list ap)
{
	int		i;
	int		k;

	va_copy(cp, ap);
	i = 0;
	if (!(*((*frm) + i) >= 48 && *((*frm) + i) <= 57))
	{
		va_end(cp);
		return (0);
	}
	k = 0;
	while ((*((*frm) + i) >= 48 && *((*frm) + i) <= 57))
		k = k * 10 + *((*frm) + i++) - 48;
	if (*((*frm) + i) != 36)
	{
		va_end(cp);
		return (0);
	}
	*frm += i + 1;
	while (k-- > 1)
		va_arg(cp, int);
	va_end(cp);
	return (1);
}
