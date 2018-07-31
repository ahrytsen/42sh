/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_reverse_search.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:42:23 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/03 16:42:27 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static int	gsh_r_search_check(t_hist *hist)
{
	char *ptr;

	ptr = NULL;
	while (hist)
	{
		if (hist->tmp)
			ptr = hist->tmp;
		else if (hist->str)
			ptr = hist->str;
		if (ptr && ft_strstr(ptr, g_srch_buf))
			return (1);
		hist = hist->prv;
	}
	return (0);
}

void		rewind_cursor(size_t len, t_pos *pos)
{
	while (len)
	{
		if ((len + pos->prompt) % pos->col == 0)
		{
			tputs(tgetstr("up", 0), 1, ft_putint);
			tputs(tgoto(tgetstr("RI", 0), 1, pos->col - 1), 1, ft_putint);
		}
		else
			tputs(tgetstr("le", 0), 1, ft_putint);
		len--;
	}
}

static void	gsh_r_yhrec(char *out, char **str)
{
	t_hist	*hist;
	char	*ptr;

	hist = gsh_r_history_bucket(RETURN, NULL);
	if (g_srch_buf[0] && gsh_r_search_check(hist))
	{
		while (hist)
		{
			if (hist->tmp)
				ptr = hist->tmp;
			else if (hist->str)
				ptr = hist->str;
			if (ft_strstr(ptr, g_srch_buf))
				break ;
			hist = gsh_r_history_bucket(PGUP, ptr);
		}
		*str = "}\e[32m?\e[0m ";
		ft_bzero((void *)out, LINE_SIZE);
		ft_strcpy(out, ptr);
	}
	else if (g_srch_buf[0])
		*str = "}\e[31m?\e[0m ";
}

void		gsh_r_search(t_ych u, char *out, t_pos *pos)
{
	char	*str;
	size_t	len;

	if (u.d != 18)
	{
		len = ft_strlen(g_srch_buf) + pos->kur + 4;
		rewind_cursor(len, pos);
		str = "}? ";
		if (u.d == 127 && g_srch_buf[0])
			g_srch_buf[ft_strlen(g_srch_buf) - 1] = 0;
		else if (u.d > 31 && u.d != 127)
			ft_strcat(g_srch_buf, u.c);
		gsh_r_yhrec(out, &str);
		tputs(tgetstr("cd", 0), 1, ft_putint);
		ft_dprintf(0, "{%s%s", g_srch_buf, str);
		tputs(out, 1, ft_putint);
		pos->len = ft_strlen(out);
		pos->kur = pos->len;
		if (!((pos->prompt + 4 + ft_strlen(g_srch_buf) + pos->len) % pos->col))
			write(0, "\n", 1);
	}
}
