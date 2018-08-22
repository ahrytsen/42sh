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

// static int	gsh_h_write_history(char *str, int mod)
// {
// 	int		fd;
// 	t_hist	*hist;
//
// 	if (!str)
// 		str = gsh_get_env("HISTFILE");
// 	if ((fd = open(str, mod, S_IRUSR | S_IWUSR)) != -1)
// 	{
// 		hist = gsh_r_history_bucket(RETURN, NULL);
// 		while (hist->prv)
// 			hist = hist->prv;
// 		while (hist)
// 		{
// 			write(fd, hist->str, ft_strlen(hist->str));
// 			write(fd, "\n", 1);
// 			hist = hist->nxt;
// 		}
// 		close(fd);
// 		return (0);
// 	}
// 	return (1);
// }

int			gsh_h_usage(int err)
{
	if (err == 1)
		ft_putendl_fd("history: -d option requires an argument", 2);
	if (err == 2)
		ft_putendl_fd("history: numeric argument required", 2);
	ft_putendl_fd("history usage:\n\thistory [-c] [-d offset] [n]\n\t\
history -awrn [filename]\n\thistory -ps arg [arg...]", 2);
	return (1);
}

static void	gsh_h_print_last(int num)
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

static int	gsh_h_sum_func(char **av)
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
		gsh_h_print_last(ft_atoi(*av));
	else
		return (gsh_h_usage(2));
	return (0);
}

int			ft_history(char **av)
{
	if (*av && **av == '-')
	{
		if (*(*av + 1) == '-')
			return (gsh_h_sum_func(av + 1));
		if (*(*av + 1) == 'c')
			;// erase history
		else if (*(*av + 1) == 's')
			;// add record
		else if (*(*av + 1) == 'p')
			;// show without add
		else if (*(*av + 1) == 'd')
			;// erase record
		else if (*(*av + 1) == 'a')
			;// append in file
		else if (*(*av + 1) == 'n')
			;// append from file
		else if (*(*av + 1) == 'r')
			;// read from file
		else if (*(*av + 1) == 'w')
			;// write in file
		else
			return (gsh_h_usage(0));
		return (0);
	}
	return (gsh_h_sum_func(av));
}
