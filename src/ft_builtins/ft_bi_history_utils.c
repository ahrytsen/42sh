/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_history_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 17:57:19 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/17 17:58:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"

int			ft_hist_usage(int err)
{
	if (err == 1)
		ft_putendl_fd("history: -d option requires an argument", 2);
	if (err == 2)
		ft_putendl_fd("history: numeric argument required", 2);
	ft_putendl_fd("history usage:\n\thistory [-c] [-d offset] [n]\n\t\
history -awrn [filename]\n\thistory -ps arg [arg...]", 2);
	return (1);
}

void	ft_hist_erase(void)
{
	t_hist	*tmp;
	t_hist	*hist;

	if (!(hist = get_term()->hist))
		return ;
	while (hist->next)
		hist = hist->next;
	while (hist)
	{
		tmp = hist;
		hist = hist->prev;
		if (tmp->tmp)
			line_tostr(&tmp->tmp, 2);
		line_tostr(&tmp->line, 2);
		free(tmp);
	}
	get_term()->hist = NULL;
}

static int	mega_uber_trivial_name_fo_function(t_hist *hist, t_hist *prev,
	unsigned num)
{
	t_hist *tmp;

	tmp = hist->next;
	line_tostr(&hist->line, 2);
	line_tostr(&hist->tmp, 2);
	free(hist);
	if (prev)
		prev->next = tmp;
	if (tmp)
		tmp->prev = prev;
	while (tmp)
	{
		prev = tmp;
		tmp->no = num;
		get_term()->hist = tmp;
		tmp = tmp->next;
		num++;
	}
	return (0);
}

int			ft_hist_erase_rec(char *str)
{
	t_hist		*hist;
	t_hist		*tmp;
	unsigned	num;

	if (!str)
		return (ft_hist_usage(1));
	if (!ft_isnumber(str))
		return (ft_hist_usage(2));
	if ((hist = get_term()->hist))
	{
		tmp = NULL;
		num = (unsigned)ft_atoi(str);
		while (hist->prev)
			hist = hist->prev;
		while (hist)
		{
			if (hist->no == num)
				return (mega_uber_trivial_name_fo_function(hist, tmp, num));
			tmp = hist;
			hist = hist->next;
		}
	}
	return (0);
}
