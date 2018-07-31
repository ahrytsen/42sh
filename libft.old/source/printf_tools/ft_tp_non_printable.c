/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_non_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 16:51:26 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/24 16:51:27 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_non_len(char *s, int *flags)
{
	int i;

	i = 1;
	if (!s)
	{
		if (flags[7] == -1)
		{
			flags[7] = 6;
			return (6);
		}
		return (flags[7]);
	}
	while (*s)
	{
		if (*s > 31 && *s < 127)
			i++;
		else
			i += 2;
		s++;
	}
	return (i);
}

static void	string_out(char *str, int *flags, int len)
{
	char	*mask;
	int		i;

	i = 0;
	mask = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";
	while (i < len && (flags[7] < 0 || i < flags[7]))
	{
		if (*str < 32 || *str == 127)
		{
			flags[9] += write(g_fd, "^", 1);
			if (*str < 32)
				flags[9] += write(g_fd, &(mask[(int)*str]), 1);
			else
				flags[9] += write(g_fd, "?", 2);
			i++;
		}
		else
			flags[9] += write(g_fd, str, 1);
		str++;
		i++;
	}
}

int			ft_print_non_print(const char **frm, va_list ap, int *flags)
{
	char	*str;
	int		len;

	(*frm)++;
	str = va_arg(ap, char *);
	len = ft_non_len(str, flags);
	if (len < flags[7])
		flags[6] -= flags[7];
	else
		flags[6] -= len;
	if (!flags[1] && flags[6] > 0)
		ft_print_width(flags);
	if (!str)
		flags[9] += write(g_fd, "(null)", flags[7]);
	else
		string_out(str, flags, len);
	if (flags[1] && flags[6] > 0)
		ft_print_width(flags);
	return (flags[9]);
}

/*
**		PRINT WIDTH
*/

void		ft_print_length(int *flags)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (flags[6] + 1));
	flags[9] += flags[6];
	while (i < flags[6])
	{
		str[i] = ' ';
		i++;
	}
	write(g_fd, str, i);
	free(str);
}

void		ft_print_width(int *flags)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (flags[6] + 1));
	flags[9] += flags[6];
	while (i < flags[6])
	{
		if (flags[3])
			str[i] = '0';
		else
			str[i] = ' ';
		i++;
	}
	write(g_fd, str, i);
	free(str);
}
