/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 14:33:48 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/27 20:35:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_bg_byid(t_list *jobs, char *str_id)
{
	int		id;
	t_job	*job;

	id = ft_atoi(str_id);
	while (jobs && (id >= 0 || jobs->next)
			&& (int)jobs->content_size != id)
		jobs = jobs->next;
	if ((!jobs || !jobs->content)
		&& ((id == -1 && ft_dprintf(2, "42sh: fg: no current job\n"))
			|| ft_dprintf(2, "42sh: fg: %s: no such job\n", str_id)))
		return (256);
	id = (int)jobs->content_size;
	job = jobs->content;
	if ((job->st == -1
			&& ft_dprintf(2, "42sh: bg: job %d already in background\n", id))
		|| (!WIFSTOPPED(job->st)
			&& ft_dprintf(2, "42sh: bg: job %d has terminated\n", id)))
		return (256);
	job->st = -1;
	kill(-job->pgid, SIGCONT);
	ft_printf("[%d] - %d continued\t", id, job->cmd->pid);
	ft_cmdlst_print(job->cmd);
	ft_printf("\n");
	return (0);
}

int			ft_bg(char **av)
{
	int		ret;

	ret = 0;
	if (!get_environ()->is_interactive
		&& ft_dprintf(2, "42sh: fg: no job control\n"))
		return (256);
	if (!*av)
		ret = ft_bg_byid(get_environ()->jobs, "-1");
	else
		while (*av)
			if (ft_bg_byid(get_environ()->jobs, *av++))
				ret = 256;
	return (ret);
}
