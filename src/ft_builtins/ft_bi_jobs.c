/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:13:02 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/20 21:48:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	job_usage(char c)
{
	ft_dprintf(2, "42sh: jobs: -%c: invalid option\n"
			   "jobs: usage: jobs [-l|-p] [job_id...]\n", c);
	return (1);
}

void		ft_print_tokens(t_list *toks)
{
	t_token	*tok;

	while (toks)
	{
		tok = toks->content;
		if (tok->type == redir)
			ft_printf(toks->next ? "%d%s %s " : "%d%s %s\n",
					tok->data.redir.left, ft_tname(tok), tok->data.redir.right);
		else
			ft_printf(toks->next ? "%s " : "%s\n", ft_tname(tok));
		toks = toks->next;
	}
}

void			ft_cmd_print(t_cmd *cmdlst)
{
	char	**av;

	while (cmdlst && cmdlst->prev)
		cmdlst = cmdlst->prev;
	while (cmdlst)
	{
		cmdlst->prev ? ft_printf("\n\t%d\t\t| ", cmdlst->pid) : 0;
		av = cmdlst->av;
		while (av && *av)
			ft_printf("%s ", *av++);
		cmdlst = cmdlst->next;
	}
	write(1, "\n", 1);
}

void		ft_print_status(int st)
{
	if (st == -1)
		ft_printf("Running ");
	else if (!st || st == 126 || st == 127)
		ft_printf(!st ? "Done\t\t" : "Done(%d)\t\t", st);
	else if (WIFEXITED(st))
		ft_printf("Done(%d)\t\t", WEXITSTATUS(st));
	else if (WIFSTOPPED(st))
	{
		ft_printf("Stopped (");
		if (WSTOPSIG(st) == SIGTSTP)
			ft_printf("SIGTSTP)\t\t");
		else if (WSTOPSIG(st) == SIGSTOP)
			ft_printf("SIGSTOP)\t\t");
		else if (WSTOPSIG(st) == SIGTTIN)
			ft_printf("SIGTTIN)\t\t");
		else if (WSTOPSIG(st) == SIGTTOU)
			ft_printf("SIGTTOU)\t\t");
	}
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
			ft_cmd_print(cmds);
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
		jobs = jobs->next;
	jobs ? job_show(jobs->content, options, cur, id)
		: ft_dprintf(2, "42sh: jobs: %d: no such job", id);
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
			if (job_by_id(get_environ()->jobs, options, ft_atoi(*av)))
				ret = 1;
	return (ret);
}
