/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:37:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/26 12:39:02 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_stop_job(t_cmd *cmd, int mod)
{
	t_job	new_job;
	t_list	*tmp;

	new_job.cmd = cmd;
	new_job.pgid = get_environ()->pgid;
	if ((tmp = ft_job_push_back(&get_environ()->jobs, &new_job)))
	{
		if (mod)
		{
			ft_printf("\n[%d] + %d suspended\t", tmp->content_size, cmd->pid);
			ft_cmdlst_print(cmd);
			ft_printf("\n");
		}
		else
			ft_printf("[%d] %d\n", tmp->content_size, cmd->pid);
	}
	else
		ft_dprintf(2, "42sh: malloc error\n");
}

static void	ft_cmdlst_wait(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pid > 0 && !cmd->ret)
		{
			waitpid(cmd->pid, &cmd->ret, WUNTRACED);
			WIFSTOPPED(cmd->ret) ? ft_stop_job(cmd, 1) : 0;
		}
		cmd = cmd->prev;
	}
}

int			ft_control_job(t_cmd *cmd, int bg, int cont)
{
	int	ret;

	ret = cmd->ret;
	if (!cmd->ret && cmd->pid)
	{
		if (get_environ()->is_interactive)
		{
			setpgid(cmd->pid, get_environ()->pgid);
			!bg ? tcsetpgrp(0, get_environ()->pgid) : 0;
		}
		cont ? kill(-get_environ()->pgid, SIGCONT) : 0;
		!bg ? ft_cmdlst_wait(cmd) : ft_stop_job(cmd, 0);
		!bg && get_environ()->is_interactive
			? tcsetpgrp(0, get_environ()->sh_pgid) : 0;
		!bg && WIFSTOPPED(cmd->ret) ? ft_stop_job(cmd, 1) : 0;
	}
	else if (cmd->ret || !cmd->pid)
		ft_cmdlst_wait(cmd->prev);
	ret = cmd->ret;
	cmd->ret = 0;
	get_environ()->pgid = 0;
	get_environ()->pid = 0;
	return (ret);
}

int			ft_status_job(int st)
{
	if (st != 126 && st != 127)
	{
		if (WIFEXITED(st))
			st = WEXITSTATUS(st);
		else if (WIFSTOPPED(st))
			st = -WSTOPSIG(st);
		else if (WIFSIGNALED(st))
			st = -WTERMSIG(st);
	}
	return (st);
}
