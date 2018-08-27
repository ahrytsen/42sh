/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:46:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/27 20:56:33 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_fg_byid(t_list **jobs, int id, int *st)
{
	t_job	*job;

	if (!jobs)
		return (1);
	while (*jobs && (id >= 0 || (*jobs)->next)
			&& (int)(*jobs)->content_size != id)
		jobs = &(*jobs)->next;
	if (!*jobs || !(*jobs)->content)
		return (1);
	id = (int)(*jobs)->content_size;
	job = (*jobs)->content;
	(*jobs)->content = NULL;
	get_environ()->pgid = job->pgid;
	get_environ()->pid = job->cmd->pid;
	ft_printf("[%d] - %d continued\t", id, job->cmd->pid);
	ft_cmdlst_print(job->cmd);
	ft_printf("\n");
	st ? (*st = ft_control_job(job->cmd, 0, 1)) : 0;
	if (st && !WIFSTOPPED(*st))
		job->cmd = ft_cmdlst_del(job->cmd);
	free(job);
	ft_jobs_clean_lst(&get_environ()->jobs);
	return (0);
}

int			ft_fg(char **av)
{
	int		st;
	int		ret;

	st = 0;
	ret = 0;
	if ((!get_environ()->is_interactive
			&& ft_dprintf(2, "42sh: fg: no job control\n"))
		|| (!*av && !get_environ()->jobs
			&& ft_dprintf(2, "42sh: fg: no curent job\n")))
		return (256);
	if (!*av)
		ret = ft_fg_byid(&get_environ()->jobs, -1, &st);
	else
		while (*av)
		{
			if (ft_fg_byid(&get_environ()->jobs, ft_atoi(*av), &st)
				&& ft_dprintf(2, "42sh: fg: %s: no such job\n", *av))
				ret = 256;
			av++;
		}
	return (ret ? ret : st);
}
