/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_sci_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 12:29:34 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/24 12:29:38 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**		some exponential form
*/

static void	ft_put_exp(int *flgs, int exp, char c)
{
	if (c == 'e')
		write(g_fd, "e", 1);
	else
		write(g_fd, "E", 1);
	if (exp < 0)
		write(g_fd, "-", 1);
	else
		write(g_fd, "+", 1);
	flgs[7] = 2;
	flgs[9] += 2;
	ft_put_sg(exp, flgs, 2);
}

static void	exp_rabbin(double d, int *flgs, int exp, char c)
{
	int len;

	len = 1;
	if (flgs[3] && flgs[6] > 0)
		len += flgs[6];
	if (!non_printable(d, flgs, c))
	{
		if ((flgs[0] || flgs[2]) && d > 0.0)
			flgs[9] += write(g_fd, "+", flgs[0]) + write(g_fd, " ", flgs[2]);
		if (d < 0.0 || 1.0 / d == 1.0 / -0.0)
		{
			flgs[9] += write(g_fd, "-", 1);
			d = -d;
		}
		ft_put_dbl(d, flgs, 1, len);
		ft_put_rem(d, flgs);
		ft_put_exp(flgs, exp, c);
	}
}

static int	find_exp(double *d, int *flgs)
{
	int		len;
	int		exp;

	exp = 0;
	len = ft_dbl_len(*d, flgs);
	while (len > 1)
	{
		*d /= 10;
		len--;
		exp++;
	}
	while ((int)(*d) == 0)
	{
		*d *= 10;
		exp--;
	}
	if (1.0 / *d != 1.0 / -0.0)
		*d += ft_set_correction(*d, flgs[7]);
	if ((int)(*d) > 9)
	{
		*d /= 10;
		exp++;
	}
	return (exp);
}

int			science_exp(const char **frm, va_list ap, int *flgs)
{
	double	d;
	int		exp;

	if (flgs[7] < 0)
		flgs[7] = 6;
	d = va_arg(ap, double);
	exp = 0;
	if (is_nan_inf_zero(d) == 0)
		exp = find_exp(&d, flgs);
	if (flgs[7] > 0 && is_nan_inf_zero(d) < 3)
		flgs[6] -= flgs[7] + 5 + ft_sg_nbrlen((long long)exp, 0);
	else if (!flgs[7] && is_nan_inf_zero(d) < 3)
		flgs[6] -= 4 + ft_sg_nbrlen((long long)exp, 0);
	else
		flgs[6] -= 3;
	if (((flgs[0] || flgs[2]) && d >= 0) || is_nan_inf_zero(d) == 2 || d < 0.0)
		flgs[6]--;
	if (!flgs[1] && flgs[6] > 0 && (is_nan_inf_zero(d) > 2 || !flgs[3]))
		ft_print_length(flgs);
	if (!non_printable(d, flgs, **frm))
		exp_rabbin(d, flgs, exp, **frm);
	if (flgs[1] && flgs[6] > 0)
		ft_print_length(flgs);
	(*frm)++;
	return (flgs[9]);
}
