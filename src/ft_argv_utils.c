/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:25:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:22:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		parse_dollar(t_buf **cur, char **line)
{
	char	*st;
	char	*tmp;

	st = *line;
	if (*st == '0' && (*line)++)
	{
		ft_putstr_mshbuf(cur, "msh", -1);
		return ;
	}
	else if (!ft_isalnum(*st) && *st != '_')
	{
		ft_putchar_mshbuf(cur, '$');
		return ;
	}
	while (ft_isalnum(**line) || **line == '_')
		(*line)++;
	tmp = ft_strsub(st, 0, *line - st);
	ft_putstr_mshbuf(cur, ft_getenv(tmp), -1);
	free(tmp);
}

void		ft_quote(t_buf **cur, char **line)
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

void		ft_bquote(t_buf **cur, char **line, uint8_t q)
{
	t_buf	*head;
	t_buf	*tmp;
	char	*str;

	if (!(head = ft_memalloc(sizeof(t_buf))) || !line)
		return ;
	tmp = head;
	while (**line != '`')
		if (!**line)
			break ;
		else if (**line == '\\' && (*line)++)
			(q ? ft_dquote_slash : ft_slash)(&tmp, line);
		else
			ft_putchar_mshbuf(&tmp, *(*line)++);
	str = ft_buftostr(head);
	if (*str)
		ft_bquote_helper(cur, str);
	free(str);
	**line ? (*line)++ : 0;
}

static void	ft_dquote(t_buf **cur, char **line)
{
	while (**line != '"')
		if (!**line)
			break ;
		else if (**line == '\\' && (*line)++)
			ft_dquote_slash(cur, line);
		else if (**line == '$' && (*line)++)
			parse_dollar(cur, line);
		else if (**line == '`' && (*line)++)
			ft_bquote(cur, line, 1);
		else
			ft_putchar_mshbuf(cur, *(*line)++);
	**line ? (*line)++ : 0;
}

char		*parse_argv(char *line)
{
	char	*tmp;
	t_buf	*head;
	t_buf	*cur;

	tmp = line;
	if (!(head = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	cur = head;
	while (*line)
		if (*line == '\\' && line++)
			ft_slash(&cur, &line);
		else if (*line == '$' && line++)
			parse_dollar(&cur, &line);
		else if (*line == '~' && line == tmp
				&& (*(line + 1) == '/' || !*(line + 1)) && line++)
			ft_putstr_mshbuf(&cur, ft_getenv("HOME"), -1);
		else if (*line == '\'' && line++)
			ft_quote(&cur, &line);
		else if (*line == '`' || *line == '"')
			(*line++ == '"') ? ft_dquote(&cur, &line)
				: ft_bquote(&cur, &line, 0);
		else
			ft_putchar_mshbuf(&cur, *line++);
	return (ft_buftostr(head));
}
