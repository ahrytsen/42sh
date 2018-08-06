/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:41:55 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/06 17:50:48 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_pl_make(int pl[2], t_cmd *cmd)
{
	if (cmd->prev)
	{
		dup2(pl[0], 0);
		close(pl[0]);
		close(pl[1]);
	}
	if (cmd->next)
	{
		if (pipe(pl) && ft_dprintf(2, "21sh: pipe error\n"))
			return (1);
		dup2(pl[1], 1);
	}
	return (0);
}

static int	ft_cmd_exec_chld(t_cmd *cmd, int bg)
{
	if (cmd->next || cmd->prev || bg)
	{
		ft_set_sh_signal(bg ? S_CHLD : S_CHLD_FG);
		bg = -1;
	}
	if (ft_redirection(cmd->toks) || (!(cmd->av = ft_argv_make(cmd->toks))
								&& ft_dprintf(2, "21sh: malloc error\n")))
		cmd->ret = 1;
	else
		cmd->ret = ft_argv_exec(cmd->av, NULL, bg);
	cmd->pid = get_environ()->pid;
	get_environ()->pgid = cmd->pid;
	ft_redirection_close(cmd->toks);
	if (cmd->next || cmd->prev || bg)
		exit(cmd->av ? cmd->ret : 1);
	return (cmd->av ? cmd->ret : 1);
}

static int	ft_cmd_exec(t_cmd *cmd, int bg)
{
	static int	pl[2];

	if (ft_pl_make(pl, cmd))
		return (1);
	if ((cmd->next || cmd->prev || bg) && (cmd->pid = fork()))
	{
		if (cmd->pid == -1 && ft_dprintf(2, "21sh: fork() error\n"))
			return (1);
		get_environ()->pid = cmd->pid;
		cmd->av = ft_argv_make(cmd->toks);
		if (get_environ()->is_interactive)
		{
			!get_environ()->pgid ? get_environ()->pgid = cmd->pid : 0;
			setpgid(get_environ()->pid, get_environ()->pgid);
		}
		return (0);
	}
	else
		return (ft_cmd_exec_chld(cmd, bg));
}

int			ft_cmdlst_exec(t_cmd *cmd, int bg)
{
	int	ret;
	int	ret2;

	while (1)
	{
		cmd->ret = ft_cmd_exec(cmd, bg);
		ft_fildes(FD_RESTORE);
		if (cmd->ret || !cmd->next)
			break ;
		cmd = cmd->next;
	}
	ret = cmd->ret;
	ret2 = ft_control_job(cmd, bg, 0);
	if (ret || (!WIFSTOPPED(ret2) && !bg))
		ft_cmdlst_del(cmd);
	return (ret2);
}
