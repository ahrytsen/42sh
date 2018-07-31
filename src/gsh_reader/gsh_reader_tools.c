/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:40:40 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/27 13:40:41 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

int			ft_putint(int c)
{
	return (write(0, &c, 1));
}

void		gsh_r_shift_right(t_pos *pos)
{
	pos->kur++;
	if ((pos->kur + pos->prompt) % pos->col == 0)
	{
		tputs(tgetstr("do", 0), 1, ft_putint);
		tputs(tgetstr("cr", 0), 1, ft_putint);
	}
	else
		tputs(tgetstr("nd", 0), 1, ft_putint);
}

void		gsh_r_shift_left(t_pos *pos)
{
	if ((pos->kur + pos->prompt) % pos->col == 0)
	{
		tputs(tgetstr("up", 0), 1, ft_putint);
		tputs(tgoto(tgetstr("RI", 0), 1, pos->col - 1), 1, ft_putint);
	}
	else
		tputs(tgetstr("le", 0), 1, ft_putint);
	pos->kur--;
}

void		gsh_r_signal(int signo)
{
	if (signo == SIGWINCH)
	{
		sum_save_function_for_winsize(1, 0);
		gsh_r_redraw_line(NULL, NULL, 0, 0);
	}
}
