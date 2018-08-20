/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:11:42 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/20 17:13:36 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	tmp = lst1->next;
	lst1->next = lst2;
	while (lst2->next)
		lst2 = lst2->next;
	lst2->next = tmp;
}
