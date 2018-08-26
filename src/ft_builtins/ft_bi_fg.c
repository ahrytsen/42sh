/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:46:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/26 12:36:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/*static int	ft_fg_byid(int id)
{
	t_list	*tmp;
	t_list	*jobs;
	t_job	*job;
	int		ret;
	int		cur_id;

	jobs = get_environ()->jobs;
	cur_id = ft_lstsize(jobs);
	if (!get_environ()->jobs)
	{
		ft_dprintf(2, "fg: no current job\n");
		return (256);
	}
	tmp = get_environ()->jobs->next;
	job = get_environ()->jobs->content;
	free(get_environ()->jobs);
}
*/

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
	ft_dprintf(2, "[%d] - %d continued\t", ft_lstsize(get_environ()->jobs),
				job->cmd->pid);
	ft_cmdlst_print(job->cmd);
	ft_printf("\n");
	ret = ft_control_job(job->cmd, 0, 1);
	if (!WIFSTOPPED(ret))
		job->cmd = ft_cmdlst_del(job->cmd);
	free(job);
	return (ret);
}
