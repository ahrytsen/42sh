/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 13:59:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/06 20:19:55 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_if_interactive(void)
{
	while (tcgetpgrp(get_environ()->sh_terminal) !=
			(get_environ()->sh_pgid = getpgrp()))
		kill(-get_environ()->sh_pgid, SIGTTIN);
	ft_set_sh_signal(S_SH);
	setpgid(get_environ()->sh_pid, get_environ()->sh_pid);
	get_environ()->sh_pgid = getpgrp();
	tcsetpgrp(get_environ()->sh_terminal, get_environ()->sh_pgid);
}

void		ft_fildes(int mod)
{
	if (mod == FD_BACKUP)
	{
		get_environ()->bkp_fd[0] = dup2(0, 100);
		get_environ()->bkp_fd[1] = dup2(1, 101);
		get_environ()->bkp_fd[2] = dup2(2, 102);
	}
	else if (mod == FD_RESTORE)
	{
		get_environ()->bkp_fd[0] == -1
			? close(0) : dup2(get_environ()->bkp_fd[0], 0);
		get_environ()->bkp_fd[1] == -1
			? close(1) : dup2(get_environ()->bkp_fd[1], 1);
		get_environ()->bkp_fd[2] == -1
			? close(2) : dup2(get_environ()->bkp_fd[2], 2);
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
	else if (mod & (S_CHLD | S_CHLD_FG)
			&& (get_environ()->pid = getpid())
			&& get_environ()->is_interactive)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		if (!get_environ()->pgid)
			get_environ()->pgid = get_environ()->pid;
		setpgid(get_environ()->pid, get_environ()->pgid);
		(mod & S_CHLD_FG) ? tcsetpgrp(0, get_environ()->pgid) : 0;
	}
}

void		ft_init_fd(int fd)
{
	get_environ()->sh_terminal = fd;
	if ((get_environ()->is_interactive = (isatty(get_environ()->sh_terminal)
										&& isatty(2))))
		ft_if_interactive();
}

void		ft_init(int ac, char **av)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;
	char		buf[MAXPATHLEN];

	ft_bzero(get_environ(), sizeof(t_env));
	if ((get_environ()->argv = ft_strdup_arr(av)))
		get_environ()->argc = ac - 1;
	ft_fildes(FD_BACKUP);
	get_environ()->envar = ft_strdup_arr(environ);
	ft_init_shell_var();
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_set_tool("SHLVL", tmp, 1, ENVAR);
	free(tmp);
	ft_set_tool("PATH", "/usr/bin:/bin", 0, ENVAR);
	ft_set_tool("PWD", getcwd(buf, MAXPATHLEN), 1, ENVAR);
	ft_unset_tool("OLDPWD", SHVAR);
	ft_set_tool("OLDPWD", NULL, 1, -1);
	get_environ()->sh_pid = getpid();
	get_environ()->sh_pgid = getpgrp();
}
