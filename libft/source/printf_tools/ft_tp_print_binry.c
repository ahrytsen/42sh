/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_print_binry.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 14:15:52 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/24 14:15:57 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**		some binary representation of unsigned numbers
*/

static unsigned long long	ft_check_bin(int i, char c, va_list ap)
{
	if (i == 0 && c != 'B')
		return (va_arg(ap, unsigned));
	if (i == 1 || c == 'B')
		return (va_arg(ap, unsigned long));
	if (i == 2 && c != 'B')
		return (va_arg(ap, unsigned long long));
	if (i == 3 && c != 'B')
		return ((unsigned short)va_arg(ap, int));
	if (i == 4 && c != 'B')
		return ((unsigned char)va_arg(ap, int));
	if (i == 5 && c != 'B')
		return (va_arg(ap, uintmax_t));
	if (i == 6 && c != 'B')
		return (va_arg(ap, size_t));
	return (0);
}

static char					*binary_converter(unsigned long long bin,
									char *str)
{
	int		i;

	i = 0;
	if (bin == 0)
	{
		str[i] = '0';
		i++;
	}
	while (bin != 0)
	{
		if (bin % 2 == 1)
			str[i] = '1';
		else
			str[i] = '0';
		i++;
		bin /= 2;
	}
	while (i % 4 != 0)
	{
		str[i] = '0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void					reverse(char *str, int len)
{
	char	c;
	int		i;

	i = 0;
	while (i < len / 2)
	{
		c = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = c;
		i++;
	}
}

int							ft_print_binary(const char **frm,
											va_list ap, int *flags)
{
	char				*str;
	char				*copy;
	int					len;

	(*frm)++;
	str = (char *)malloc(sizeof(char) * 80);
	binary_converter(ft_check_bin(flags[8], **frm, ap), str);
	len = ft_strlen(str);
	flags[6] -= len;
	if (!flags[1] && flags[6] > 0)
		ft_print_length(flags);
	reverse(str, len);
	copy = str;
	while (len)
	{
		flags[9] += write(g_fd, copy, 4);
		if (len > 4)
			flags[9] += write(g_fd, " ", 1);
		copy += 4;
		len -= 4;
	}
	if (flags[1] && flags[6] > 0)
		ft_print_length(flags);
	free(str);
	return (flags[9]);
}
