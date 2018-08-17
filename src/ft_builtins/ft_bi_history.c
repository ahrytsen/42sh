/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 15:33:28 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/07 15:33:32 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"

static int	ft_hist_write(char *str, int mod)
{
	int		fd;
	t_hist	*hist;
	char	*line;

	if (!str)
		str = ft_getenv("HISTFILE");
	if ((fd = open(str, mod, S_IRUSR | S_IWUSR)) != -1)
	{
		hist = get_term()->hist;
		while (hist->prev)
			hist = hist->prev;
		while (hist)
		{
			line = line_tostr(&hist->line, 0);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
			hist = hist->next;
		}
		close(fd);
		return (0);
	}
	return (1);
}

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

static void	ft_hist_print_last(int num)
{
	int		i;
	t_hist	*hist;
	char	*str;

	i = 0;
	hist = get_term()->hist;
	while (hist->next)
		hist = hist->next;
	while (hist->prev && i < num)
	{
		hist = hist->prev;
		i++;
	}
	while (hist->next)
	{
		str = line_tostr(&hist->line, 0);
		ft_printf("%5d  %s\n", hist->no, str);
		free(str);
		hist = hist->next;
	}
}

static int	ft_hist_reveal(char **av)
{
	t_hist	*hist;
	char	*str;

	if (!*av)
	{
		hist = get_term()->hist;
		while (hist->prev)
			hist = hist->prev;
		while (hist)
		{
			str = line_tostr(&hist->line, 0);
			ft_printf("%5d  %s\n", hist->no, str);
			free(str);
			hist = hist->next;
		}
	}
	else if (ft_isnumber(*av))
		ft_hist_print_last(ft_atoi(*av));
	else
		return (ft_hist_usage(2));
	return (0);
}

static void	ft_hist_erase(void)
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

int			ft_history(char **av)
{
	if (*av && **av == '-')
	{
		if (*(*av + 1) == '-')
			return (ft_hist_reveal(av + 1));
		if (*(*av + 1) == 'c')
			ft_hist_erase();
		else if (*(*av + 1) == 's')
			ft_hist_add_rec();// add record
		else if (*(*av + 1) == 'p')
			ft_hist_show_without_add(av + 1);// show without add
		else if (*(*av + 1) == 'd')
			return (ft_hist_erase_rec(*(av + 1)));// erase record
		else if (*(*av + 1) == 'a')
			return (ft_hist_write(*(av + 1), 01011));
		else if (*(*av + 1) == 'n')
			ft_hist_read(*(av + 1));// append from file
		else if (*(*av + 1) == 'r')
			ft_hist_init(*(av + 1));// read from file
		else if (*(*av + 1) == 'w')
			return (ft_hist_write(*(av + 1), 03001));
		else
			return (ft_hist_usage(0));
		return (0);
	}
	return (ft_hist_reveal(av));
}
