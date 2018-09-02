/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:38:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:16:57 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_curhome(void)
{
	while (get_term()->curx || get_term()->cury)
		ft_curleft(1);
	ft_prompt();
}

void	ft_curleft(int mod)
{
	if (get_term()->curx == 0 && get_term()->cury >= 0)
	{
		get_term()->curx = get_term()->width - 1;
		get_term()->cury--;
		tputs(tgetstr("up", NULL), 1, term_print);
		tputs(tgoto(tgetstr("ch", NULL), 1, get_term()->width - mod),
			1, term_print);
	}
	else if (get_term()->cury >= 0)
	{
		get_term()->curx--;
		if (mod)
			tputs(tgoto(get_term()->cm_left, 1, 1), 1, term_print);
	}
}

void	ft_curright(int mod)
{
	if (get_term()->curx == get_term()->width - 1)
	{
		get_term()->curx = 0;
		get_term()->cury++;
		tputs(tgetstr("do", NULL), 1, term_print);
		tputs(tgetstr("cr", NULL), 1, term_print);
		if (!mod)
			tputs(tgetstr("cd", NULL), 1, term_print);
	}
	else if (get_term()->cury >= 0)
	{
		get_term()->curx++;
		if (mod)
			tputs(get_term()->cm_right, 1, term_print);
	}
}

void	ft_curnleft(int mod, int n)
{
	while (n--)
		ft_curleft(mod);
}

void	ft_curnright(int mod, int n)
{
	while (n--)
		ft_curright(mod);
}
