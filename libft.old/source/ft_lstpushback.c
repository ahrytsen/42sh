/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:42:56 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/30 16:45:47 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list *cope;

	if (alst)
	{
		if (!*alst)
			*alst = new;
		else
		{
			cope = *alst;
			while (cope->next)
				cope = cope->next;
			cope->next = new;
		}
	}
}
