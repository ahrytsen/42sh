/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:37:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/20 22:23:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_stop_job(t_cmd *cmd, int mod)
{
	t_list	*jobs_tmp;
	t_job	*job;

	job = NULL;
	jobs_tmp = NULL;
	if ((jobs_tmp = ft_memalloc(sizeof(t_list)))
		&& (job = ft_memalloc(sizeof(t_job))))
	{
		jobs_tmp->content = job;
		ft_lstadd(&get_environ()->jobs, jobs_tmp);
		job->cmd = cmd;
		job->pgid = get_environ()->pgid;
		if (mod)
		{
			ft_dprintf(2, "\n[%d] + %d suspended\t",
						ft_lstsize(get_environ()->jobs), job->cmd->pid);
			ft_cmdlst_print(job->cmd);
		}
	}
	else
	{
		free(job);
		free(jobs_tmp);
	}
}

static void	ft_bg_job(t_cmd *cmd)
{
	ft_dprintf(2, "[%d] %d\n", ft_lstsize(get_environ()->jobs) + 1,
				get_environ()->pid);
	ft_stop_job(cmd, 0);
}

static void	ft_kill_all(t_cmd *cmd)
{
	while ((cmd = cmd->prev))
	{
		cmd->pid > 0 ? waitpid(cmd->pid, &cmd->ret, WUNTRACED) : 0;
		cmd->ret = ft_status_job(cmd->ret);
	}
}

int			ft_control_job(t_cmd *cmd, int bg, int cont)
{
	int	ret;

	ret = cmd->ret;
	if (!cmd->ret && cmd->pid && get_environ()->is_interactive)
	{
		setpgid(cmd->pid, get_environ()->pgid);
		!bg ? tcsetpgrp(0, get_environ()->pgid) : 0;
		cont ? kill(-get_environ()->pgid, SIGCONT) : 0;
		!bg ? waitpid(cmd->pid, &cmd->ret, WUNTRACED) : ft_bg_job(cmd);
		!bg ? tcsetpgrp(0, get_environ()->sh_pgid) : 0;
		!bg && WIFSTOPPED(cmd->ret) ? ft_stop_job(cmd, 1) : 0;
	}
	else if (!cmd->ret && cmd->pid)
		waitpid(cmd->pid, &cmd->ret, 0);
	if (ret || (!WIFSTOPPED(cmd->ret) && !bg))
		ft_kill_all(cmd);
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
			st = WSTOPSIG(st);
		else if (WIFSIGNALED(st))
			st = WTERMSIG(st);
	}
	return (st);
}
