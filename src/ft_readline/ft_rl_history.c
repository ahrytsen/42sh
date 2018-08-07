/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:05:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 16:01:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		hist_init(void)
{
	t_hist	*new_hist;

	if (!get_term()->hist || get_term()->hist->line)
	{
		if (!(new_hist = ft_memalloc(sizeof(t_hist)))
			|| !(new_hist->tmp = ft_memalloc(sizeof(t_line))))
			return (-1);
		new_hist->no = ((get_term()->hist)? get_term()->hist->no + 1 : 1);
		if (!get_term()->hist)
			get_term()->hist = new_hist;
		else
		{
			get_term()->hist->next = new_hist;
			new_hist->prev = get_term()->hist;
			get_term()->hist = new_hist;
		}
	}
	else if (!get_term()->hist->tmp)
		if (!(get_term()->hist->tmp = ft_memalloc(sizeof(t_line))))
			return (-1);
	get_term()->cursor = get_term()->hist->tmp;
	return (1);
}

void	hist_move(uint64_t buf)
{
	t_hist	*tmp;

	tmp = (buf == K_UP ? get_term()->hist->prev : get_term()->hist->next);
	if (tmp && get_term()->prompt == P_USER)
	{
		get_term()->hist = tmp;
		if (!get_term()->hist->tmp)
			get_term()->hist->tmp = copy_line(get_term()->hist->line);
		ft_curhome();
		get_term()->hist->tmp ? get_term()->cursor = get_term()->hist->tmp : 0;
		ft_redraw_line();
	}
	else
		write(0, "\a", 1);
}

void	clean_hist(void)
{
	while (get_term()->hist->prev)
		get_term()->hist = get_term()->hist->prev;
	while (1)
	{
		get_term()->hist->tmp ? line_tostr(&get_term()->hist->tmp, 2) : 0;
		if (!get_term()->hist->next)
			return ;
		get_term()->hist = get_term()->hist->next;
	}
}

void	hist_commit(int st, int i)
{
	t_line	*to_save;

	to_save = get_term()->hist->tmp;
	get_term()->hist->tmp = NULL;
	clean_hist();
	if (i && to_save->prev && st > 0 && get_term()->prompt == P_USER)
		get_term()->hist->line = to_save;
	else if (i && st > 0 && get_term()->prompt == P_USER)
		get_term()->hist->tmp = to_save;
	else if (st > 0)
		line_tostr(&get_term()->cursor, 2);
}
