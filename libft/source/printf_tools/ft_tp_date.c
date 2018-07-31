/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tp_date.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 12:27:51 by dlinkin           #+#    #+#             */
/*   Updated: 2017/12/25 12:27:53 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	month(int time, t_date *date)
{
	char	*arr;
	int		i;

	i = 0;
	arr = "\37\34\37\36\37\36\37\37\36\37\36\37";
	if ((date->yy % 4 == 0 && !(date->yy % 100 == 0)) ||
		(date->yy % 100 == 0 && date->yy % 400 == 0))
		arr = "\37\35\37\36\37\36\37\37\36\37\36\37";
	while (i < 12)
	{
		if (time < (int)arr[i])
		{
			date->mon = i + 1;
			break ;
		}
		time -= (int)arr[i];
		i++;
	}
	return (time);
}

static void	make_date(int time, t_date *date)
{
	int		y;

	date->hh = (time % 86400) / 3600;
	date->mm = (time % 86400) / 60 % 60;
	date->ss = (time % 86400) - date->hh * 3600 - date->mm * 60;
	time /= 86400;
	y = 1970;
	while (time > 364)
	{
		if ((y % 4 == 0 && !(y % 100 == 0)) || (y % 100 == 0 && y % 400 == 0))
			if (time > 365)
				time -= 366;
			else
				break ;
		else
			time -= 365;
		y++;
	}
	date->yy = y;
	date->dd = month(time, date) + 1;
}

static char	*jidoa(char *tmp, int num, int zero, int len)
{
	char	*str;

	str = "JanFebMarAprMayJunJulAugSepOctNovDec";
	if (zero)
	{
		tmp[0] = str[3 * num - 3];
		tmp[1] = str[3 * num - 2];
		tmp[2] = str[3 * num - 1];
		tmp[3] = '\0';
		return (tmp);
	}
	tmp[len] = '\0';
	if (num < 10)
	{
		tmp[0] = '0';
		len++;
	}
	while (len)
	{
		tmp[len - 1] = num % 10 + 48;
		num /= 10;
		len--;
	}
	return (tmp);
}

static int	make_some_string(t_date *dt, char *str, int size)
{
	char tmp[5];

	str[0] = '\0';
	if (size == 0)
	{
		ft_strcat(str, jidoa(tmp, dt->yy, 0, ft_sg_nbrlen(dt->yy, 0)));
		ft_strcat(str, " ");
		ft_strcat(str, jidoa(tmp, dt->mon, 1, 0));
		ft_strcat(str, " ");
		ft_strcat(str, jidoa(tmp, dt->dd, 0, ft_sg_nbrlen(dt->dd, 0)));
		ft_strcat(str, " ");
		ft_strcat(str, jidoa(tmp, dt->hh, 0, ft_sg_nbrlen(dt->hh, 0)));
		ft_strcat(str, ":");
		ft_strcat(str, jidoa(tmp, dt->mm, 0, ft_sg_nbrlen(dt->mm, 0)));
		return (17);
	}
	ft_strcat(str, jidoa(tmp, dt->mon, 1, 0));
	ft_strcat(str, " ");
	ft_strcat(str, jidoa(tmp, dt->dd, 0, ft_sg_nbrlen(dt->dd, 0)));
	ft_strcat(str, " ");
	ft_strcat(str, jidoa(tmp, dt->hh, 0, ft_sg_nbrlen(dt->hh, 0)));
	ft_strcat(str, ":");
	ft_strcat(str, jidoa(tmp, dt->mm, 0, ft_sg_nbrlen(dt->mm, 0)));
	return (12);
}

int			ft_print_date(const char **frm, va_list ap, int *flags)
{
	int		time;
	t_date	date[6];
	char	str[25];
	int		len;

	time = va_arg(ap, int);
	make_date(time, date);
	len = make_some_string(date, str, flags[8]);
	if (flags[7] > -1 && !(len < flags[7]))
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
