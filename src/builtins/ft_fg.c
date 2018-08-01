/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:46:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:20:19 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			ft_count_fg(t_list *proc)
{
	if (!proc)
		return (0);
	return (ft_count_fg(proc->next) + 1);
}

int			ft_fg(char **av)
{
	t_list	*tmp;
	t_job	*job;
	int		ret;

	(void)av;
	if (!get_environ()->jobs)
	{
		ft_dprintf(2, "fg: no current job\n");
		return (256);
	}
	tmp = get_environ()->jobs->next;
	job = get_environ()->jobs->content;
	free(get_environ()->jobs);
	get_environ()->jobs = tmp;
	get_environ()->pgid = job->pgid;
	get_environ()->pid = job->cmd->pid;
	ft_dprintf(2, "[%d] - %d continued\t", ft_count_fg(get_environ()->jobs),
				job->cmd->pid);
	ft_cmdlst_print(job->cmd);
	ret = ft_control_job(job->cmd, 0, 1);
	if (!WIFSTOPPED(ret))
		job->cmd = ft_cmdlst_del(job->cmd);
	free(job);
	return (ret);
}
