/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 03:23:42 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/31 05:09:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

void	ft_quote(t_buf **cur, char **line)
{
	char	*st;

	st = *line;
	while (**line != '\'')
	{
		if (!**line)
			break ;
		(*line)++;
	}
	ft_putstr_mshbuf(cur, st, *line - st);
	**line ? (*line)++ : 0;
}

void	ft_dquote(t_buf **cur, char **line)
{
	while (**line != '"')
		if (!**line)
			break ;
		else if (**line == '\\' && *(*line + 1) == '\n')
			*line += 2;
		else if (**line == '\\' && (*line)++)
			ft_dquote_slash(cur, line);
		else
			ft_putchar_mshbuf(cur, *(*line)++);
	**line ? (*line)++ : 0;
}

void	remove_quotes(t_list *lst)
{
	char	*s;
	t_buf	*buf;
	t_buf	*head;

	if (!lst || !lst->content || !(buf = ft_memalloc(sizeof(t_buf))))
		return ;
	head = buf;
	s = lst->content;
	while (*s)
		if (*s == '\\' && *(s + 1) == '\n')
			s += 2;
		else if (*s == '\\' && s++)
			ft_slash(&buf, &s);
		else if (*s == '\'' && s++)
			ft_quote(&buf, &s);
		else if (*s == '"' && s++)
			ft_dquote(&buf, &s);
		else
			ft_putchar_mshbuf(&buf, *s++);
	free(lst->content);
	lst->content = ft_buftostr(head);
}
