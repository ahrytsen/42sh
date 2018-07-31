/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_sym.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 14:09:25 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/25 14:09:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**	PRINTABLE CHARACTERS & CONTROL CHARACTERS
*/

static void	gsh_r_backspace(char *out, t_pos *pos)
{
	if (pos->kur == pos->len)
		out[pos->len - 1] = 0;
	else
		ft_memmove(out + pos->kur - 1, out + pos->kur, ft_strlen(out)
			- pos->kur + 1);
	if ((pos->kur + pos->prompt) % pos->col == 0)
	{
		tputs(tgetstr("up", 0), 1, ft_putint);
		tputs(tgoto(tgetstr("RI", 0), 1, pos->col - 1), 1, ft_putint);
	}
	else
		tputs(tgetstr("le", 0), 1, ft_putint);
	gsh_r_redraw_line(out, pos, 1, 1);
	pos->len--;
	pos->kur--;
}

void		gsh_r_prnt_char(t_ych u, char *out, t_pos *pos, size_t size)
{
	if (u.d != 127)
	{
		if (pos->kur < pos->len)
			ft_memmove(out + pos->kur + size, out + pos->kur, ft_strlen(out)
				- pos->kur);
		ft_memcpy(out + pos->kur, u.c, size);
		pos->kur += size;
		pos->len += size;
		if (out[0])
			gsh_r_redraw_line(out, pos, size, 1);
		if ((pos->kur + pos->prompt) % pos->col == 0)
		{
			if (pos->kur == pos->len)
				tputs(tgetstr("do", 0), 1, ft_putint);
			tputs(tgetstr("cr", 0), 1, ft_putint);
		}
	}
	else if (u.d == 127)
		gsh_r_backspace(out, pos);
}

void		gsh_r_search_switch(char *out, t_pos *pos)
{
	g_srch_md ^= 1;
	if (g_srch_md)
	{
		while (pos->kur)
			gsh_r_shift_left(pos);
		tputs(tgetstr("cd", 0), 1, ft_putint);
		ft_dprintf(0, "%s", "{}? ");
	}
	else
	{
		rewind_cursor(ft_strlen(g_srch_buf) + 4 + pos->kur, pos);
		tputs(tgetstr("cd", 0), 1, ft_putint);
	}
	ft_bzero((void *)g_srch_buf, SRCH_BUF_SIZE);
	tputs(out, 1, ft_putint);
	pos->len = ft_strlen(out);
	pos->kur = pos->len;
}

int			gsh_r_ctrl_char(char c, char *out, t_pos *pos)
{
	if (c == 10 || (c == 4 && *out) || c == 3)
	{
		gsh_r_home_end_tab('F', NULL, pos);
		c == 3 ? ft_bzero(out, LINE_SIZE) : 0;
		write(0, "\n", 1);
		return (1);
	}
	else if (c == 4 && !*out)
	{
		gsh_r_home_end_tab('F', NULL, pos);
		write(0, "\n", 1);
		return (0);
	}
	else if (c == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		gsh_r_redraw_line(NULL, NULL, 0, 0);
	}
	else if (c == 9)
		gsh_r_autocomplete(out, pos);
	else if (c == 18)
		gsh_r_search_switch(out, pos);
	return (2);
}
