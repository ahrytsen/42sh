/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:37:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/05 19:07:21 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_jobs_update(t_list **jobs)
{
	t_list	*tmp;
	t_job	*job;
	int		w_st;

	if (!jobs)
		return ;
	while ((tmp = *jobs))
	{
		if ((job = (*jobs)->content)
			&& (w_st = waitpid(job->cmd->pid,
								&job->st, WUNTRACED | WNOHANG)))
		{
			job_by_id(get_environ()->jobs, J_DEF, (*jobs)->content_size);
			if (w_st == -1
				|| (w_st > 0 && (WIFEXITED(job->st) || WIFSIGNALED(job->st))))
			{
				*jobs = (*jobs)->next;
				job->cmd = ft_cmdlst_del(job->cmd);
				free(job);
				free(tmp);
				continue ;
			}
		}
		jobs = &(*jobs)->next;
	}
}

void		ft_stop_job(t_cmd *cmd, int mod)
{
	t_job	new_job;
	t_list	*tmp;

	new_job.cmd = cmd;
	new_job.pgid = get_environ()->pgid;
	new_job.st = (mod ? cmd->ret : -1);
	if ((tmp = ft_job_push_back(&get_environ()->jobs, &new_job)))
	{
		if (mod && get_environ()->is_interactive)
		{
			ft_printf("\n[%d] + %d suspended\t", tmp->content_size, cmd->pid);
			ft_cmdlst_print(cmd);
			ft_printf("\n");
		}
		else if (get_environ()->is_interactive)
			ft_printf("[%d] %d\n", tmp->content_size, cmd->pid);
	}
	else
		ft_dprintf(2, "42sh: malloc error\n");
}

static void	ft_cmdlst_wait(t_cmd *cmd)
{
	char	*tmp;

	while (cmd)
	{
		if (cmd->pid > 0 && !cmd->ret)
			waitpid(cmd->pid, &cmd->ret, WUNTRACED);
		if (WIFSTOPPED(cmd->ret))
		{
			ft_stop_job(cmd, 1);
			return ;
		}
		else if (WIFSIGNALED(cmd->ret)
				&& (tmp = ft_get_job_error(WTERMSIG(cmd->ret))))
			ft_dprintf(2, "%s: %d\n", tmp, WTERMSIG(cmd->ret));
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
	}
	else if (cmd->ret || !cmd->pid)
		ft_cmdlst_wait(cmd->prev);
	ret = cmd->ret;
	cmd->ret = 0;
	get_environ()->pgid = 0;
	get_environ()->pid = 0;
	!cont ? ft_jobs_update(&get_environ()->jobs) : 0;
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
