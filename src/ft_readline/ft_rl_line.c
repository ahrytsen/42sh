/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:25:08 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/26 15:30:39 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_line	*copy_line(t_line *line)
{
	t_line	*copy;

	if (!(copy = ft_memalloc(sizeof(t_line))))
		return (NULL);
	while (line->prev)
		line = line->prev;
	while (line->next)
	{
		if (line_add(copy, line->ch) == -1)
			return ((t_line*)line_tostr(&copy, 2));
		line = line->next;
	}
	return (copy);
}

char	*line_tostr(t_line **cursor, int mod)
{
	size_t	size;
	char	*line;
	t_line	*tmp;

	line = NULL;
	tmp = *cursor;
	while (tmp->next)
		tmp = tmp->next;
	size = ft_strlen((char*)&tmp->ch) + 1;
	while (tmp->prev)
	{
		tmp = tmp->prev;
		size += ft_strlen((char*)&tmp->ch);
	}
	if (mod != 2 && !(line = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	while (tmp->next)
	{
		mod != 2 ? ft_strcat(line, (char*)&tmp->ch) : 0;
		tmp = tmp->next;
		mod ? ft_memdel((void**)&tmp->prev) : 0;
	}
	mod == 2 ? ft_memdel((void**)&tmp) : 0;
	mod == 2 ? *cursor = NULL : 0;
	return (line);
}

int		line_bs(t_line *cursor)
{
	t_line	*tmp;

	if (!(tmp = cursor->prev))
		return (1);
	tmp = tmp->prev;
	ft_memdel((void**)&cursor->prev);
	cursor->prev = tmp;
	tmp ? tmp->next = cursor : 0;
	return (0);
}

int		line_add(t_line *cursor, uint64_t ch)
{
	t_line	*tmp;
	t_line	*new_ch;

	if (!(new_ch = ft_memalloc(sizeof(*new_ch))))
		return (-1);
	new_ch->ch = ch;
	tmp = cursor->prev;
	cursor->prev = new_ch;
	new_ch->next = cursor;
	new_ch->prev = tmp;
	if (tmp)
		tmp->next = new_ch;
	return (1);
}
