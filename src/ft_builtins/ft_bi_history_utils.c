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

int				ft_hist_usage(int err)
{
	if (err == 1)
		ft_putendl_fd("history: -d option requires an argument", 2);
	if (err == 2)
		ft_putendl_fd("history: numeric argument required", 2);
	ft_putendl_fd("history usage:\n\thistory [-c] [-d offset] [n]\n\t\
history -awrn [filename]\n\thistory -ps arg [arg...]", 2);
	return (1);
}

void			ft_hist_erase(void)
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

static t_hist	*ft_hist_re_link(t_hist *hist, unsigned num)
{
	t_hist *tmp;
	t_hist *prev;

	tmp = hist->next;
	prev = hist->prev;
	line_tostr(&hist->line, 2);
	if (hist->tmp)
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
	return (prev);
}

int				ft_hist_erase_rec(char *str)
{
	t_hist		*hist;
	unsigned	num;

	if (!str)
		return (ft_hist_usage(1));
	if (!ft_isnumber(str))
		return (ft_hist_usage(2));
	if ((hist = get_term()->hist))
	{
		num = (unsigned)ft_atoi(str);
		while (hist->prev)
			hist = hist->prev;
		while (hist)
		{
			if (hist->no == num)
			{
				get_term()->hist = ft_hist_re_link(hist, num);
				break ;
			}
			hist = hist->next;
		}
	}
	return (0);
}

void			ft_hist_add_rec(char **av)
{
	t_line	*line;
	char	*tmp;

	if (!*av)
		return ;
	if (get_term()->hist && (line = get_term()->hist->line))
		line_tostr(&line, 2);
	line = (t_line *)ft_memalloc(sizeof(t_line));
	while (*av)
	{
		tmp = *av;
		while (*tmp)
			line_add(line, ft_get_unichar(&tmp));
		line_add(line, (uint64_t)(' '));
		av++;
	}
	if (!get_term()->hist)
		get_term()->hist = (t_hist *)ft_memalloc(sizeof(t_hist));
	get_term()->hist->line = line;
}
