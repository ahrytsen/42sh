/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_sci_flo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 12:29:45 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/24 12:29:47 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**		float numbers output
*/

void		ft_put_dbl(double n, int *flags, int i, int len)
{
	char				*ptr;
	unsigned long long	l;

	ptr = (char *)malloc(sizeof(char) * len);
	len--;
	while (len)
	{
		l = n;
		if (flags[5] && i % 3 == 0 && i != 0 && n > 0)
		{
			ptr[len] = ',';
			len--;
		}
		ptr[len] = l % 10 + 48;
		n /= 10.0;
		len--;
		i++;
	}
	l = n;
	ptr[len] = l % 10 + 48;
	flags[9] += write(g_fd, ptr, i);
	free(ptr);
}

void		ft_put_rem(double n, int *flags)
{
	int		i;
	char	*str;

	if (flags[7])
	{
		str = (char *)malloc(sizeof(char) * (flags[7] + 1));
		i = 1;
		str[0] = '.';
		while (i <= flags[7])
		{
			str[i] = (unsigned long long)(n * 10 -
			(unsigned long long)n * 10) % 10 + 48;
			i++;
			n *= 10.0;
		}
		flags[9] += write(g_fd, str, flags[7] + 1);
		free(str);
	}
}

/*
**		some floating form
*/

static void	float_rabbin(double d, int *flgs, int len, char c)
{
	if (flgs[3] && flgs[6] > 0)
	{
		if (len > 1)
			len += flgs[6];
		else
			len += flgs[6];
	}
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
	}
}

int			science_float(const char **frm, va_list ap, int *flgs)
{
	double	d;
	int		len;

	if (flgs[7] < 0)
		flgs[7] = 6;
	d = va_arg(ap, double);
	if (1.0 / d != 1.0 / -0.0)
		d += ft_set_correction(d, flgs[7]);
	len = ft_dbl_len(d, flgs);
	if (flgs[7] > 0)
		flgs[6] -= len + flgs[7] + 1;
	else
		flgs[6] -= len;
	if (((flgs[0] || flgs[2]) && d >= 0) || is_nan_inf_zero(d) == 2 || d < 0.0)
		flgs[6]--;
	if (!flgs[1] && flgs[6] > 0 && (is_nan_inf_zero(d) > 2 || !flgs[3]))
		ft_print_length(flgs);
	float_rabbin(d, flgs, len, **frm);
	if (flgs[1] && flgs[6] > 0 && !flgs[3])
		ft_print_length(flgs);
	(*frm)++;
	return (flgs[9]);
}
