/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_drawing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:11:03 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/21 12:11:05 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void	gsh_redraw_on_resize(char *save_out, t_pos *save_pos)
{
	size_t	kur;

	kur = save_pos->kur + save_pos->prompt;
	if (g_srch_md)
		kur += ft_strlen(g_srch_buf) + 4;
	tputs(tgoto(tgetstr("LE", 0), 1, kur), 1, ft_putint);
	tputs(tgetstr("cd", 0), 1, ft_putint);
	gsh_prompt(1);
	if (g_srch_md)
		ft_dprintf(0, "{%s%s", g_srch_buf, "}? ");
	tputs(save_out, 1, ft_putint);
	if (save_pos->len != save_pos->kur)
		tputs(tgoto(tgetstr("LE", 0), 1, save_pos->len - save_pos->kur)
			, 1, ft_putint);
}

void		gsh_r_redraw_line(char *out, t_pos *pos, size_t size, int mod)
{
	static char		*save_out;
	static t_pos	*save_pos;

	if (mod == 1)
	{
		tputs(tgetstr("cd", 0), 1, ft_putint);
		ft_dprintf(0, "%s", out + pos->kur - size);
		if (pos->len != pos->kur)
			tputs(tgoto(tgetstr("LE", 0), 1, pos->len - pos->kur)
				, 1, ft_putint);
	}
	else if (mod == 2)
	{
		save_out = out;
		save_pos = pos;
		save_pos->kur = 0;
		save_pos->len = 0;
		save_pos->col = (size_t)tgetnum("co");
	}
	else if (mod == 0)
		gsh_redraw_on_resize(save_out, save_pos);
}

void		sum_save_function_for_winsize(int mod, t_pos *pos)
{
	static t_pos *save;

	if (mod == 0)
		save = pos;
	else if (mod == 1)
	{
		tgetent(0, getenv("TERM"));
		save->col = (size_t)tgetnum("co");
	}
}
