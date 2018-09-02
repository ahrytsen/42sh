/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:13:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/27 17:19:50 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	job_usage(char c)
{
	ft_dprintf(2, "42sh: jobs: -%c: invalid option\n"
				"jobs: usage: jobs [-l|-p] [job_id...]\n", c);
	return (256);
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
		ft_printf("\n");
	}
}

static void	job_iter(t_list *jobs, int options)
{
	int	i;
	int	num_jobs;
	int	cur;

	i = 0;
	num_jobs = ft_count_jobs(jobs);
	while (jobs)
	{
		if (jobs->content)
		{
			i++;
			if (i < num_jobs - 1)
				cur = 0;
			else
				cur = (i == num_jobs ? 2 : 1);
			job_show(jobs->content, options, cur, jobs->content_size);
		}
		jobs = jobs->next;
	}
}

int			job_by_id(t_list *jobs, int options, size_t id)
{
	int	i;
	int	cur;
	int	num_jobs;

	i = 0;
	num_jobs = ft_count_jobs(jobs);
	while (jobs)
	{
		jobs->content ? i++ : 0;
		if (jobs->content_size == id)
			break ;
		jobs = jobs->next;
	}
	if (i < num_jobs - 1)
		cur = 0;
	else
		cur = (i == num_jobs ? 2 : 1);
	jobs && jobs->content ? job_show(jobs->content, options, cur, id)
		: ft_dprintf(2, "42sh: jobs: %d: no such job\n", id);
	return (jobs && jobs->content);
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
		job_iter(get_environ()->jobs, options);
	else
		while (*av)
			if (job_by_id(get_environ()->jobs, options, ft_atoi(*av++)))
				ret = 256;
	return (ret);
}
