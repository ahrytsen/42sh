/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:35:29 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/21 18:02:55 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static void	ft_init_termcap(void)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		ft_fatal(1, exit,
				"Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatal(1, exit, "Could not access the termcap data base.\n");
	else if (!success)
		ft_fatal(1, exit, "Terminal type `%s' is not defined.\n", termtype);
	get_term()->clear = tgetstr("ce", NULL);
	get_term()->cm_left = tgetstr("le", NULL);
	get_term()->cm_right = tgetstr("nd", NULL);
	get_term()->iv_on = tgetstr("mr", NULL);
	get_term()->iv_off = tgetstr("me", NULL);
	get_term()->del_ch = tgetstr("DC", NULL);
}

static void	sig_handler(int signo)
{
	struct winsize	w;

	if (signo == SIGINT)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
		get_term()->prompt = P_USER;
		get_term()->is_inter = 1;
		ft_readline_ret();
	}
	else if (signo == SIGWINCH)
	{
		ft_curhome();
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		get_term()->height = w.ws_row;
		get_term()->width = w.ws_col;
		ft_redraw_line();
	}
	else if (signo == SIGTSTP)
		write(2, "\a", 1);
}

static void	ft_set_rl_signal(int mod)
{
	struct sigaction int_handler;

	if (mod == T_INIT)
	{
		ft_bzero(&int_handler, sizeof(struct sigaction));
		int_handler.sa_handler = sig_handler;
		sigaction(SIGINT, &int_handler, 0);
		signal(SIGWINCH, sig_handler);
		signal(SIGTSTP, sig_handler);
	}
	else
	{
		ft_set_sh_signal(S_SH);
		signal(SIGWINCH, SIG_DFL);
	}
}

void		ft_terminal(int mod)
{
	static int	already_saved = 0;

	if (!isatty(get_environ()->sh_terminal))
		ft_fatal(1, exit, "42sh: fd isn't valid terminal type device.\n");
	else if (mod == T_INIT && !already_saved)
	{
		ft_bzero(get_term(), sizeof(t_term));
		ft_init_termcap();
		tcgetattr(get_environ()->sh_terminal, &get_term()->savetty);
		get_term()->work_tty = get_term()->savetty;
		get_term()->work_tty.c_lflag &= ~(ICANON | ECHO);
		get_term()->work_tty.c_lflag |= TOSTOP;
		get_term()->work_tty.c_cc[VMIN] = 1;
		get_term()->work_tty.c_cc[VTIME] = 0;
		get_term()->comp_stage = -1;
		get_term()->hist_max_size = (unsigned)ft_atoi(ft_getenv("HISTSIZE"));
		ft_hist_init(NULL);
		already_saved = 1;
	}
	ft_set_rl_signal(mod);
	if (mod == T_INIT)
		tcsetattr(get_environ()->sh_terminal, TCSAFLUSH, &get_term()->work_tty);
	else
		tcsetattr(get_environ()->sh_terminal, TCSANOW, &get_term()->savetty);
}

int			ft_is_interrupted(void)
{
	if (get_term()->is_inter)
	{
		get_term()->is_inter = 0;
		return (1);
	}
	return (0);
}
