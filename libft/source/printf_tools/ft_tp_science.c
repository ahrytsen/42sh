/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_science.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:25:13 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/17 18:25:14 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**		it's a floating numbers printing
*/

int			is_nan_inf_zero(double d)
{
	unsigned		s;
	unsigned		e;
	unsigned long	m;
	t_soviet		f;

	f.fl = d;
	s = (f.dw >> 63);
	e = (f.dw >> 52) & 0x7FF;
	m = (f.dw & 0xFFFFFFFFFFFFF);
	if (s == 0 && e == 0 && m == 0)
		return (1);
	if (s == 1 && e == 0 && m == 0)
		return (2);
	if (s == 0 && e == 2047 && m == 0)
		return (3);
	if (s == 1 && e == 2047 && m == 0)
		return (4);
	if (e == 2047 && m != 0)
		return (5);
	return (0);
}

int			ft_dbl_len(double d, int *flags)
{
	int		i;
	double	cp;

	if (is_nan_inf_zero(d) > 2)
	{
		if (flags[7])
			return (3 - flags[7] - 1);
		return (3);
	}
	i = 1;
	cp = d;
	while (cp >= 10.0 || cp <= -10.0)
	{
		cp /= 10;
		i++;
	}
	if (flags[5])
		i += (i - 1) / 3;
	return (i);
}

double		ft_set_correction(double d, int prec)
{
	int		i;
	double	c;
	double	corr;

	if (d < 0.0)
		c = -d;
	else
		c = d;
	corr = 1.0;
	i = 0;
	while (i < prec)
	{
		c *= 10.0;
		corr /= 10.0;
		i++;
	}
	if ((unsigned long long)(c * 10 - (unsigned long long)c * 10) % 10 < 5)
		return (0.0);
	if (d < 0.0)
		return (-corr);
	return (corr);
}

int			non_printable(double d, int *flags, char c)
{
	int i;

	i = is_nan_inf_zero(d);
	if (i < 3)
		return (0);
	if ((flags[0] || flags[2]) && i == 3)
		flags[9] += write(g_fd, "+", flags[0]) + write(g_fd, " ", flags[2]);
	if (i == 4)
		flags[9] += write(g_fd, "-", 1);
	if (i > 2)
		flags[9] += 3;
	if (i == 3 || i == 4)
		c > 96 ? write(g_fd, "inf", 3) : write(g_fd, "INF", 3);
	if (i == 5)
		c > 96 ? write(g_fd, "nan", 3) : write(g_fd, "NAN", 3);
	return (1);
}

int			ft_print_science(const char **frm, va_list ap, int *flags)
{
	if (**frm == 'f' || **frm == 'F')
		return (science_float(frm, ap, flags));
	return (science_exp(frm, ap, flags));
}
