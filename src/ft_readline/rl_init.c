/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:35:29 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:38:32 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static void	sig_handler(int signo)
{
	struct winsize	w;

	if (signo == SIGINT)
	{
		get_term()->st_sel = NULL;
		get_term()->end_sel = NULL;
		get_term()->prompt = P_USER;
		get_term()->is_inter = 1;
		if (isatty(0) && !get_environ()->pid)
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
		ft_dprintf(2, "\a");
}

static void	ft_set_rl_signal(void)
{
	struct sigaction int_handler;

	ft_bzero(&int_handler, sizeof(struct sigaction));
	int_handler.sa_handler = sig_handler;
	sigaction(SIGINT, &int_handler, 0);
	signal(SIGWINCH, sig_handler);
	signal(SIGTSTP, sig_handler);
}

void		ft_terminal(int mod)
{
	static int	already_saved = 0;

	if (!isatty(0))
		ft_fatal(1, exit, "21sh: fd isn't valid terminal type device.\n");
	else if (mod == T_INIT && !already_saved)
	{
		tcgetattr(0, &get_environ()->savetty);
		get_environ()->work_tty = get_environ()->savetty;
		get_environ()->work_tty.c_lflag &= ~(ICANON | ECHO);
		get_environ()->work_tty.c_lflag |= TOSTOP;
		get_environ()->work_tty.c_cc[VMIN] = 1;
		get_environ()->work_tty.c_cc[VTIME] = 0;
		already_saved = 1;
	}
	if (mod == T_INIT)
	{
		ft_set_rl_signal();
		tcsetattr(0, TCSAFLUSH, &get_environ()->work_tty);
	}
	else
	{
		ft_set_sh_signal(S_SH);
		tcsetattr(0, TCSANOW, &get_environ()->savetty);
	}
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
