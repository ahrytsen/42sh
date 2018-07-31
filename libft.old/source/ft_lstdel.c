/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:08:23 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/01 15:08:24 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *nxt;

	if (alst && del)
	{
		tmp = *alst;
		if (tmp)
		{
			while (tmp)
			{
				nxt = tmp->next;
				if ((tmp)->content)
					del(tmp->content, tmp->content_size);
				free(tmp);
				tmp = nxt;
			}
			*alst = NULL;
		}
	}
}
