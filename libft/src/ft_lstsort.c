/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:46:03 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/01 13:46:13 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	inner_loop(t_list **head, int *mark, int count)
{
	t_list	*list;
	int		j;
	void	*data;
	size_t	size;

	j = 0;
	list = *head;
	while (j < count)
	{
		if (ft_strcmp((char *)list->content, (char *)list->next->content) > 0)
		{
			*mark = 1;
			data = list->content;
			size = list->content_size;
			list->content = list->next->content;
			list->content_size = list->next->content_size;
			list->next->content = data;
			list->next->content_size = size;
		}
		list = list->next;
		j++;
	}
}

t_list		*ft_lstsort(t_list *alst)
{
	int		i;
	int		num;
	int		mark;

	if (!alst)
		return (NULL);
	num = (int)ft_lstsize(alst);
	i = 1;
	while (i < num)
	{
		mark = 0;
		inner_loop(&alst, &mark, num - i);
		if (!mark)
			break ;
		i++;
	}
	return (alst);
}
