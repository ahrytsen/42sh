/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:45:34 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/07 14:45:35 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		set_length(const char **frm, va_list ap)
{
	int		length;
	va_list	cp;

	if (**frm == 42)
	{
		(*frm)++;
		if (ft_search_dollar(frm, cp, ap))
			return (va_arg(cp, int));
		return (va_arg(ap, int));
	}
	else
	{
		length = 0;
		while (**frm >= 48 && **frm <= 57)
		{
			length = length * 10 + **frm - 48;
			(*frm)++;
		}
	}
	return (length);
}

static int		set_precision(const char **frm, va_list ap, int prec)
{
	va_list	cp;

	if (**frm != 46)
		return (-1);
	(*frm)++;
	if (**frm == 45)
	{
		(*frm)++;
		while (**frm >= 48 && **frm <= 57)
			(*frm)++;
		return (0);
	}
	else if (**frm == 42)
	{
		(*frm)++;
		if (ft_search_dollar(frm, cp, ap))
			return (va_arg(cp, int));
		return (va_arg(ap, int));
	}
	while (**frm >= 48 && **frm <= 57)
	{
		prec = prec * 10 + **frm - 48;
		(*frm)++;
	}
	return (prec);
}

static int		set_size(const char **frm)
{
	if (**frm == 108 && ((*frm)++))
	{
		if (**frm == 108 && ((*frm)++))
			return (2);
		return (1);
	}
	if (**frm == 104 && ((*frm)++))
	{
		if (**frm == 104 && ((*frm)++))
			return (4);
		return (3);
	}
	if (**frm == 106 && ((*frm)++))
		return (5);
	if (**frm == 122 && ((*frm)++))
		return (6);
	return (0);
}

static void		set_flags(const char **f, int *flags)
{
	while (**f == 32 || **f == 48 || **f == 43 || **f == 45
		|| **f == 35 || **f == 39)
	{
		if (**f == 43)
		{
			flags[0] = 1;
			flags[2] = 0;
		}
		if (**f == 45)
		{
			flags[1] = 1;
			flags[3] = 0;
		}
		if (**f == 32 && !flags[0])
			flags[2] = 1;
		if (**f == 48 && !flags[1])
			flags[3] = 1;
		if (**f == 35)
			flags[4] = 1;
		if (**f == 39)
			flags[5] = 1;
		(*f)++;
	}
}

/*
**	flags
**	[0] +
**	[1] -
**	[2] space
**	[3] 0
**	[4] #
**	[5] '
**	[6] length
**	[7]	precision
**	[8]	size
**	[9]	'return'
*/

void			ft_set(const char **format, int *flags, va_list ap)
{
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	flags[3] = 0;
	flags[4] = 0;
	flags[5] = 0;
	set_flags(format, flags);
	flags[6] = set_length(format, ap);
	if (flags[6] < 0)
	{
		flags[1] = 1;
		flags[6] *= -1;
	}
	flags[7] = set_precision(format, ap, 0);
	flags[8] = set_size(format);
	flags[9] = 0;
}
