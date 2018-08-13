/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:59:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/03 20:34:36 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_if_interactive(void)
{
	while (tcgetpgrp(get_environ()->sh_terminal) !=
			(get_environ()->sh_pgid = getpgrp()))
		kill(-get_environ()->sh_pgid, SIGTTIN);
	ft_set_sh_signal(S_SH);
	get_environ()->sh_pid = getpid();
	setpgid(get_environ()->sh_pid, get_environ()->sh_pid);
	tcsetpgrp(get_environ()->sh_terminal, get_environ()->sh_pid);
}

void		ft_fildes(int mod)
{
	if (mod == FD_BACKUP)
	{
		get_environ()->bkp_fd[0] = fcntl(0, F_GETFD) > 0 ? dup(0) : -1;
		get_environ()->bkp_fd[1] = fcntl(1, F_GETFD) > 0 ? dup(1) : -1;
		get_environ()->bkp_fd[2] = fcntl(2, F_GETFD) > 0 ? dup(2) : -1;
	}
	else if (mod == FD_RESTORE)
	{
		if (get_environ()->bkp_fd[0] == -1)
			fcntl(0, F_GETFD) > 0 ? close(0) : 0;
		else
			dup2(get_environ()->bkp_fd[0], 0);
		if (get_environ()->bkp_fd[1] == -1)
			fcntl(1, F_GETFD) > 0 ? close(1) : 0;
		else
			dup2(get_environ()->bkp_fd[1], 1);
		if (get_environ()->bkp_fd[2] == -1)
			fcntl(2, F_GETFD) > 0 ? close(2) : 0;
		else
			dup2(get_environ()->bkp_fd[2], 2);
	}
}

void		ft_set_sh_signal(int mod)
{
	if (mod & S_SH && get_environ()->is_interactive)
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

void		ft_init_fd(int fd)
{
	get_environ()->sh_terminal = fd;
	if ((get_environ()->is_interactive = isatty(get_environ()->sh_terminal)))
		ft_if_interactive();
}

void		ft_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	ft_bzero(get_environ(), sizeof(t_env));
	ft_fildes(FD_BACKUP);
	get_environ()->envar = ft_strdup_arr(environ);
	ft_init_shell_var();
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_set_tool("SHLVL", tmp, 1, ENVAR);
	free(tmp);
	ft_set_tool("PATH", "/usr/bin:/bin", 0, ENVAR);
}
