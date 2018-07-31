/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:59:39 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/01 11:59:40 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		if (content && content_size)
		{
			list->content = malloc(sizeof(list->content) * content_size);
			if (!list->content)
			{
				free(list);
				return (NULL);
			}
			list->content = ft_memmove(list->content, content, content_size);
			list->content_size = content_size;
		}
		else
		{
			list->content = NULL;
			list->content_size = 0;
		}
		list->next = NULL;
		return (list);
	}
	return (NULL);
}
