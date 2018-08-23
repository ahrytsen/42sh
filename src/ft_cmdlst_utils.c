/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:35:56 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/23 13:06:32 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			ft_cmdlst_print(t_cmd *cmdlst)
{
	while (cmdlst && cmdlst->prev)
		cmdlst = cmdlst->prev;
	while (cmdlst)
	{
		cmdlst->prev ? write(1, " | ", 3) : 0;
		ft_cmd_print(cmdlst);
		cmdlst = cmdlst->next;
	}
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
		&& write(2, "42sh: malloc error\n", 19))
		return (ft_cmdlst_del(cmdlst));
	ft_memcpy(new_node, node, sizeof(t_cmd));
	while (cmdlst && cmdlst->next)
		cmdlst = cmdlst->next;
	cmdlst ? cmdlst->next = new_node : 0;
	new_node->prev = cmdlst;
	return (new_node);
}
