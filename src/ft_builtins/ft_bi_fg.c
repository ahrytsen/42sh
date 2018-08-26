/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:46:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/26 21:21:45 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_fg_byid(t_list **jobs, int id)
{
	int		ret;
	t_job	*job;

	if (!jobs)
		return (-1);
	while (*jobs && (id >= 0 || (*jobs)->next)
		   && (int)(*jobs)->content_size != id)
		jobs = &(*jobs)->next;
	if ((!*jobs || !(*jobs)->content)
		&& (id < 0 || ))
		return (1);
	id = (int)(*jobs)->content_size;
	job = (*jobs)->content;
	(*jobs)->content = NULL;
	get_environ()->pgid = job->pgid;
	get_environ()->pid = job->cmd->pid;
	ft_printf("[%d] - %d continued\t", id, job->cmd->pid);
	ft_cmdlst_print(job->cmd);
	ft_printf("\n");
	ret = ft_control_job(job->cmd, 0, 1);
	if (!WIFSTOPPED(ret))
		job->cmd = ft_cmdlst_del(job->cmd);
	free(job);
	ft_jobs_clean_lst(&get_environ()->jobs);
	return (ret);
}

int			ft_fg(char **av)
{
	int		ret;

	ret = 0;
	if (!*av)
		(ft_fg_byid(&get_environ()->jobs, -1) && (ret = 256))
			? ft_dprintf(2, "42sh: fg: no current job\n") : 0;
	else
		while (*av)
		{
			if (ft_fg_byid(&get_environ()->jobs, ft_atoi(*av))
				&& ft_dprintf(2, "42sh: fg: %d: no such job\n", *av))
				ret = 256;
		}
	return (ret);
}
