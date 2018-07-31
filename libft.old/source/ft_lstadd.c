/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:11:40 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/01 15:11:42 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst)
	{
		if (!*alst)
			*alst = new;
		else if (*alst && new)
		{
			new->next = *alst;
			*alst = new;
		}
	}
}
