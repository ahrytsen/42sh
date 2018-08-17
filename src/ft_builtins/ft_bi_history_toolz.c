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

void		ft_hist_init(char *str)
{
	char	*file;
	char	*line;
	int		fd;

	if (!str)
		file = ft_getenv("HISTFILE");
	else
		file = str;
	if ((fd = open(file, O_RDONLY)) != -1)
	{
		get_term()->hist_max_size = (unsigned)ft_atoi(ft_getenv("HISTSIZE"));
		while (get_next_line(fd, &line) > 0)
		{
			// gsh_r_history_bucket(CREATE, 0);					//
			// gsh_r_history_bucket(ADD, line);					//
			free(line);
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
			{
				// gsh_r_history_bucket(CREATE, 0);			//
				// gsh_r_history_bucket(ADD, line);			//
			}
			free(line);
		}
	}
}

int			ft_hist_erase_rec(char *str)
{
	if (!str)
		return (ft_hist_usage(1));
	if (!ft_isnumber(str))
		return (ft_hist_usage(2));
	// gsh_r_history_bucket(DELONE, str);						//
	return (0);
}

void		ft_hist_add_rec(void)
{
	t_line	*line;
	t_line	*tmp;
	char	sw;

	line = get_term()->hist->line;
	while (line->prev)
		line = line->prev;
	sw = 0;
	while ((!sw && line->ch != 32) || (sw && line->ch == 32))
	{
		tmp = line;
		line = line->next;
		if ((!sw && line->ch == 32) || (sw && line->ch != 32))
			sw ^= 1;
		free(tmp);
	}
	line->prev = NULL;
}

void		ft_hist_show_without_add(char **av)
{
	t_hist	*hist;
	t_hist	*tmp;

	hist = get_term()->hist;
	tmp = hist->prev;
	tmp->next = NULL;
	get_term()->hist = tmp;
	line_tostr(&hist->line, 2);
	line_tostr(&hist->tmp, 2);
	free(hist);
	while (*av)
	{
		ft_putendl(*av);
		av++;
	}
}
