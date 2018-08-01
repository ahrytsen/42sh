/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:59:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:32:41 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"

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
	get_term()->height = tgetnum("li");
	get_term()->width = tgetnum("co");
}

static void	ft_if_interactive(void)
{
	while (tcgetpgrp(get_environ()->sh_terminal) !=
			(get_environ()->sh_pgid = getpgrp()))
		kill(-get_environ()->sh_pgid, SIGTTIN);
	ft_set_sh_signal(S_SH);
	ft_init_termcap();
	get_environ()->sh_pid = getpid();
	setpgid(get_environ()->sh_pid, get_environ()->sh_pid);
	tcsetpgrp(1, get_environ()->sh_pid);
}

void		ft_fildes(int mod)
{
	if (mod == FD_BACKUP)
	{
		get_environ()->bkp_fd[0] = dup(0);
		get_environ()->bkp_fd[1] = dup(1);
		get_environ()->bkp_fd[2] = dup(2);
	}
	else if (mod == FD_RESTORE)
	{
		dup2(get_environ()->bkp_fd[0], 0);
		dup2(get_environ()->bkp_fd[1], 1);
		dup2(get_environ()->bkp_fd[2], 2);
	}
}

void		ft_set_sh_signal(int mod)
{
	if (mod & S_SH)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
	else if ((mod & (S_CHLD | S_CHLD_FG)) && get_environ()->is_interactive)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		signal(SIGWINCH, SIG_DFL);
		get_environ()->pid = getpid();
		if (!get_environ()->pgid)
			get_environ()->pgid = get_environ()->pid;
		setpgid(get_environ()->pid, get_environ()->pgid);
		(mod & S_CHLD_FG) ? tcsetpgrp(1, get_environ()->pgid) : 0;
	}
}

void		ft_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	ft_bzero(get_term(), sizeof(t_term));
	ft_bzero(get_environ(), sizeof(t_env));
	ft_fildes(FD_BACKUP);
	get_environ()->env = ft_strdup_arr(environ);
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	ft_setenv("PATH", "/usr/bin:/bin", 0);
	get_environ()->sh_terminal = STDIN_FILENO;
	if ((get_environ()->is_interactive = isatty(get_environ()->sh_terminal)))
		ft_if_interactive();
}
