/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:11:42 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/22 12:23:18 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_list **lst, t_list *node, t_list *ins)
{
	t_list	*tmp;

	if (!ins)
		return ;
	if (!node)
		ft_lstadd_list(lst, ins);
	else
	{
		tmp = *lst;
		while (tmp && tmp != node)
			tmp = tmp->next;
		if (tmp)
		{
			tmp = node->next;
			node->next = ins;
			while (ins->next)
				ins = ins->next;
			ins->next = tmp;
		}
	}
}
