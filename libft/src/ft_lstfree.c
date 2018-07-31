/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:49:49 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/30 16:50:22 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list **alst)
{
	t_list *tmp;
	t_list *nxt;

	if (alst)
	{
		tmp = *alst;
		if (tmp)
		{
			while (tmp)
			{
				nxt = tmp->next;
				if ((tmp)->content)
					free(tmp->content);
				free(tmp);
				tmp = nxt;
			}
			*alst = NULL;
		}
	}
}
