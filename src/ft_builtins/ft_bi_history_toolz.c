/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_history_toolz.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 11:58:42 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/17 11:58:47 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"

static void	ft_hist_add_entry(char *line)
{
	t_hist	*tmp;

	tmp = get_term()->hist;
	if (tmp)
	{
		tmp->next = (t_hist *)ft_memalloc(sizeof(t_hist));
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->no = tmp->prev->no + 1;
	}
	else
	{
		tmp = (t_hist *)ft_memalloc(sizeof(t_hist));
		tmp->no = 1;
	}
	tmp->line = (t_line *)ft_memalloc(sizeof(t_line));
	while (*line)
		line_add(tmp->line, ft_get_unichar(&line));
	get_term()->hist = tmp;
}

void		ft_hist_init(char *str)
{
	int			fd;

	if (!str)
		str = ft_getenv("HISTFILE");
	if ((fd = open(str, O_RDONLY)) != -1)
	{
		ft_hist_erase();
		get_term()->hist_max_size = (unsigned)ft_atoi(ft_getenv("HISTSIZE"));
		while (get_next_line(fd, &str) > 0)
		{
			ft_hist_add_entry(str);
			free(str);
		}
		close(fd);
	}
}

static int	ft_hist_search_elem(char *line)
{
	t_hist	*hist;
	char	*str;

	if (!(hist = get_term()->hist))
		return (0);
	while (hist->prev)
		hist = hist->prev;
	while (hist)
	{
		str = line_tostr(&hist->line, 0);
		if (!ft_strcmp(line, str))
		{
			free(str);
			return (1);
		}
		free(str);
		hist = hist->next;
	}
	return (0);
}

void		ft_hist_read(char *str)
{
	int		fd;
	char	*line;

	if (!str)
		str = ft_getenv("HISTFILE");
	if ((fd = open(str, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (!ft_hist_search_elem(line))
				ft_hist_add_entry(line);
			free(line);
		}
	}
}

void		ft_hist_show_without_add(char **av)
{
	t_hist	*hist;
	t_hist	*tmp;

	tmp = NULL;
	if ((hist = get_term()->hist))
	{
		tmp = hist->prev;
		if (tmp)
			tmp->next = NULL;
		if (hist->line)
			line_tostr(&hist->line, 2);
		if (hist->tmp)
			line_tostr(&hist->tmp, 2);
		free(hist);
	}
	get_term()->hist = tmp;
	while (*av)
	{
		ft_putendl(*av);
		av++;
	}
}
