/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:47:01 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/14 14:47:02 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

/*
**		CONVERT WCHAR INTO 4 * CHAR
*/

void		converter(wchar_t c, char *b)
{
	b[1] = '\0';
	b[2] = '\0';
	b[3] = '\0';
	b[4] = '\0';
	if (c < (1 << 7))
		b[0] = (char)(c);
	else if (c < (1 << 11))
	{
		b[0] = (char)((c >> 6) | 0xC0);
		b[1] = (char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 16))
	{
		b[0] = (char)(((c >> 12)) | 0xE0);
		b[1] = (char)(((c >> 6) & 0x3F) | 0x80);
		b[2] = (char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 21))
	{
		b[0] = (char)(((c >> 18)) | 0xF0);
		b[1] = (char)(((c >> 12) & 0x3F) | 0x80);
		b[2] = (char)(((c >> 6) & 0x3F) | 0x80);
		b[3] = (char)((c & 0x3F) | 0x80);
	}
}

/*
**		 PRINT STRING/WIDECHAR STRING
*/

static int	wstring(wchar_t *s, int *flags)
{
	char	str[5];
	int		len;

	flags[6] -= flags[7];
	if (!flags[1] && flags[6] > 0)
		ft_print_width(flags);
	if (!s)
		flags[9] += write(g_fd, "(null)", flags[7]);
	else
	{
		while (flags[7])
		{
			converter(*s, str);
			len = ft_strlen(str);
			flags[9] += write(g_fd, str, len);
			flags[7] -= len;
			s++;
		}
	}
	if (flags[1] && flags[6] > 0)
		ft_print_width(flags);
	return (flags[9]);
}

int			ft_print_string(const char **frm, va_list ap, int *flags)
{
	char	*str;
	wchar_t	*s;
	int		len;

	if (**frm == 's' && flags[8] != 1)
	{
		str = va_arg(ap, char *);
		len = ft_strlen_null(str);
		if (flags[7] > -1 && len > 0 && !(len < flags[7]))
			flags[6] -= flags[7];
		else
			flags[6] -= len;
		if (!flags[1] && flags[6] > 0)
			ft_print_width(flags);
		flags[9] += ft_putlen(str, flags);
		if (flags[1] && flags[6] > 0)
			ft_print_width(flags);
		(*frm)++;
		return (flags[9]);
	}
	s = va_arg(ap, wchar_t *);
	ft_wchar_len(s, flags);
	wstring(s, flags);
	(*frm)++;
	return (flags[9]);
}

/*
**		 PRINT CHARACTERS
*/

static int	ft_print_wchar(va_list ap, int *flags)
{
	char	str[5];
	int		len;

	converter((wchar_t)va_arg(ap, int), str);
	len = ft_strlen(str);
	if (len == 0)
		len++;
	flags[6] -= len;
	if (!flags[1] && flags[6] > 0)
		ft_print_width(flags);
	flags[9] += write(g_fd, str, len);
	if (flags[1] && flags[6] > 0)
		ft_print_width(flags);
	return (flags[9]);
}

int			ft_print_char(const char **frm, va_list ap, int *flags)
{
	char	c;

	if (!((**frm == 'c' && flags[8] == 1) || **frm == 'C')
		|| !(MB_CUR_MAX == 4 && ((flags[8] == 1 && **frm == 'c')
			|| **frm == 'C')))
	{
		if (**frm == 'c' || (**frm == 'C' && MB_CUR_MAX == 1))
			c = (char)va_arg(ap, int);
		else
			c = **frm;
		flags[6]--;
		if (!flags[1] && flags[6] > 0)
			ft_print_width(flags);
		write(g_fd, &c, 1);
		if (flags[1] && flags[6] > 0)
			ft_print_width(flags);
		(*frm)++;
		return (flags[9] + 1);
	}
	(*frm)++;
	return (ft_print_wchar(ap, flags));
}
