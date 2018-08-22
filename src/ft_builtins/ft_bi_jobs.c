/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:13:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/21 21:54:30 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	job_usage(char c)
{
	ft_dprintf(2, "42sh: jobs: -%c: invalid option\n"
				"jobs: usage: jobs [-l|-p] [job_id...]\n", c);
	return (1);
}

static void	job_show(t_job *job, int options, int cur, int id)
{
	t_cmd	*cmds;

	cmds = job->cmd;
	while (cmds->prev)
		cmds = cmds->prev;
	if (options == J_P)
		ft_printf("%d\n", job->pgid);
	else
	{
		ft_printf("[%d] ", id);
		if (cur)
			write(1, cur == 2 ? "+ " : "- ", 2);
		else
			write(1, "  ", 2);
		(options == J_L) ? ft_printf("%d ", cmds->pid) : 0;
		ft_print_status(job->st);
		if (options == J_L)
			ft_cmd_print_colon(cmds);
		else
			ft_cmdlst_print(cmds);
	}
}

static int	job_iter(t_list *jobs, int options, int cur)
{
	int	id;

	if (!jobs)
		return (1);
	id = job_iter(jobs->next, options, cur ? cur - 1 : cur);
	job_show(jobs->content, options, cur, id);
	return (id + 1);
}

static int	job_by_id(t_list *jobs, int options, int id)
{
	int	cur;
	int	num_jobs;

	num_jobs = ft_lstsize(jobs);
	cur = (id == num_jobs ? 2 : 0);
	cur = (id == num_jobs - 1 ? 1 : 0);
	while (jobs && num_jobs != id)
	{
		jobs = jobs->next;
		num_jobs--;
	}
	jobs ? job_show(jobs->content, options, cur, id)
		: ft_dprintf(2, "42sh: jobs: %d: no such job\n", id);
	return (jobs == NULL);
}

int			ft_jobs(char **av)
{
	int		options;
	int		ret;
	char	*tmp;

	options = J_DEF;
	ret = 0;
	while (*av && *(tmp = *av) == '-')
	{
		while (*++tmp)
			if (*tmp == 'p' || *tmp == 'l')
				options = (*tmp == 'p' ? J_P : J_L);
			else
				return (job_usage(*tmp));
		av++;
	}
	if (!*av)
		job_iter(get_environ()->jobs, options, 2);
	else
		while (*av)
			if (job_by_id(get_environ()->jobs, options, ft_atoi(*av++)))
				ret = 1;
	return (ret);
}
