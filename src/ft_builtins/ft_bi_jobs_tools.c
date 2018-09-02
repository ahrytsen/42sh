/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_jobs_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:48:14 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/27 20:36:32 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_jobs_clean_lst(t_list **jobs)
{
	if (!jobs || !*jobs)
		return ;
	ft_jobs_clean_lst(&(*jobs)->next);
	if (!(*jobs)->next && !(*jobs)->content)
		ft_memdel((void**)jobs);
}

int			ft_count_jobs(t_list *jobs)
{
	int	jobs_num;

	jobs_num = 0;
	while (jobs)
	{
		if (jobs->content)
			jobs_num++;
		jobs = jobs->next;
	}
	return (jobs_num);
}

void		ft_cmd_print_colon(t_cmd *cmdlst)
{
	while (cmdlst && cmdlst->prev)
		cmdlst = cmdlst->prev;
	while (cmdlst)
	{
		cmdlst->prev ? ft_printf("\n\t%d\t\t\t| ", cmdlst->pid) : 0;
		ft_cmd_print(cmdlst);
		cmdlst = cmdlst->next;
	}
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
	else if (WIFSIGNALED(st))
		ft_printf("Terminated(%d)\t\t", WTERMSIG(st));
}

t_list		*ft_job_push_back(t_list **jobs, t_job *new_job)
{
	int	id;

	id = 0;
	if (!jobs)
		return (NULL);
	while (*jobs && (*jobs)->content)
	{
		id++;
		jobs = &(*jobs)->next;
	}
	if (!*jobs && (!(*jobs = ft_memalloc(sizeof(t_list)))
					|| !((*jobs)->content_size = id + 1)))
		return (NULL);
	if (!((*jobs)->content = ft_memalloc(sizeof(t_job))))
		return (NULL);
	ft_memcpy((*jobs)->content, new_job, sizeof(t_job));
	return (*jobs);
}
