/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 12:35:14 by dlinkin           #+#    #+#             */
/*   Updated: 2018/07/29 12:37:07 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *list)
{
	while (list)
	{
		if (list->content)
		{
			write(1, list->content, list->content_size);
			write(1, "\n", 1);
		}
		list = list->next;
	}
}
