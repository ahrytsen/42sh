/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 12:37:32 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/10 12:37:34 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**	GSH_READER V21_05_18
**
**	MAIN CYCLE & BELL SIGNAL ON NON-VALID INPUT
*/

static int	gsh_reader_bell_chaek(t_ych in, t_pos *pos, char *out)
{
	if ((in.d == 27 || in.d == K_SHFT_DWN || in.d == K_SHFT_ALT_DWN) && !*out
		&& !g_srch_md)
		return (1);
	else if ((in.d == K_ARRW_RGHT || in.d == K_END || in.d == K_DEL || in.d ==
		K_ALT_RGHT || in.d == K_SHFT_RGHT || in.d == K_SHFT_ALT_RGHT) &&
		pos->kur == pos->len && !g_srch_md)
		return (1);
	else if ((in.d == K_ARRW_LFT || in.d == K_HOME || in.d == K_ALT_LFT
		|| in.d == K_SHFT_LFT || in.d == K_SHFT_ALT_LFT) && !(pos->kur)
		&& !g_srch_md)
		return (1);
	else if (in.d == K_ALT_UP && !((pos->kur + pos->prompt) / pos->col)
		&& !g_srch_md)
		return (1);
	else if (in.d == K_ALT_DWN && !(((pos->len + pos->prompt) /
		pos->col) - ((pos->kur + pos->prompt) / pos->col)) && !g_srch_md)
		return (1);
	else if ((in.d == 127 && !(pos->kur) && !g_srch_md) || ((in.d != 127 &&
		(int)(ft_strlen(out) + ft_strlen(in.c)) > LINE_SIZE)))
		return (1);
	else if ((in.d == K_SHFT_ALT_UP || in.d == K_SHFT_UP) && !*g_buffer)
		return (1);
	return (0);
}

static int	gsh_reader_cycle(int i, char *out, t_pos *pos)
{
	t_ych	u;

	u.d = 0;
	while ((i = read(0, u.c, 8)))
	{
		u.c[i] = 0;
		if (gsh_reader_bell_chaek(u, pos, out))
			write(0, "\a", 1);
		else if ((u.c[0] > 31 || u.c[0] == 127) && !g_srch_md)
			gsh_r_prnt_char(u, out, pos, ft_strlen(u.c));
		else if (u.c[0] < 32 && u.c[0] > -1 && u.c[0] != 27)
		{
			if ((i = gsh_r_ctrl_char(u.c[0], out, pos)) < 2)
				break ;
		}
		else if (u.c[0] == 27 && !g_srch_md)
			gsh_r_esc_seq(u, out, pos);
		if (g_srch_md && (u.c[0] > 31 || u.c[0] < 0))
			gsh_r_search(u, out, pos);
		u.d = 0;
	}
	return (i);
}

static int	gsh_reader_init(char **line, char *out, size_t prompt)
{
	t_pos	*pos;
	int		i;

	g_hst_sz = (unsigned)ft_atoi(gsh_get_env("HISTSIZE"));
	g_srch_md = 0;
	ft_bzero((void *)out, LINE_SIZE);
	pos = (t_pos *)malloc(sizeof(t_pos));
	pos->prompt = prompt;
	gsh_r_history_bucket(CREATE, 0);
	gsh_r_redraw_line(out, pos, 0, 2);
	sum_save_function_for_winsize(0, pos);
	if ((i = gsh_reader_cycle(0, out, pos)))
		*line = ft_strdup(out);
	if (ft_strchr(*line, '!'))
		*line = gsh_r_history_replace_mark(*line, 0);
	free(pos);
	return (i);
}

int			gsh_reader(char **line, size_t prompt)
{
	struct termios	tstr;
	struct termios	copy;
	char			out[LINE_SIZE];
	int				i;

	tcgetattr(0, &tstr);
	tgetent(0, gsh_get_env("TERM"));
	copy = tstr;
	tstr.c_lflag ^= ICANON;
	tstr.c_lflag ^= ECHO;
	tstr.c_lflag ^= ISIG;
	tcsetattr(0, TCSAFLUSH, &tstr);
	signal(SIGWINCH, gsh_r_signal);
	*line = NULL;
	i = gsh_reader_init(line, out, prompt);
	signal(SIGWINCH, SIG_DFL);
	tcsetattr(0, TCSANOW, &copy);
	return (i);
}
