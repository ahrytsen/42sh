/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:35:56 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:23:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			ft_cmdlst_print(t_cmd *cmdlst)
{
	char	**av;

	while (cmdlst && cmdlst->prev)
		cmdlst = cmdlst->prev;
	while (cmdlst)
	{
		cmdlst->prev ? ft_dprintf(2, " | ") : 0;
		av = cmdlst->av;
		while (av && *av)
			ft_dprintf(2, "%s ", *av++);
		cmdlst = cmdlst->next;
	}
	ft_dprintf(2, "\n");
}

t_cmd			*ft_cmdlst_del(t_cmd *cmdlst)
{
	t_cmd	*tmp;

	while (cmdlst && cmdlst->prev)
		cmdlst = cmdlst->prev;
	while (cmdlst)
	{
		tmp = cmdlst;
		cmdlst = cmdlst->next;
		ft_strarr_free(tmp->av);
		ft_lstdel(&tmp->toks, ft_token_del);
		free(tmp);
	}
	return (NULL);
}

t_cmd			*ft_cmdlst_push(t_cmd *cmdlst, t_cmd *node)
{
	t_cmd *new_node;

	if (!(new_node = (t_cmd*)malloc(sizeof(t_cmd)))
		&& ft_dprintf(2, "21sh: malloc error\n"))
		return (ft_cmdlst_del(cmdlst));
	ft_memcpy(new_node, node, sizeof(t_cmd));
	while (cmdlst && cmdlst->next)
		cmdlst = cmdlst->next;
	cmdlst ? cmdlst->next = new_node : 0;
	new_node->prev = cmdlst;
	return (new_node);
}
