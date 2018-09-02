/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:20:43 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/22 12:34:28 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_list(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			tmp = new;
			while (new->next)
				new = new->next;
			new->next = *alst;
			*alst = tmp;
		}
	}
}
