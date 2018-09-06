/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 08:15:32 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/06 21:25:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

void		record_var(t_buf **buf, char **s, char *symbols)
{
	char	*tmp;

	tmp = NULL;
	if (ft_isdigit(**s) && **s - '0' <= get_environ()->argc)
	{
		ft_putstrq_mshbuf(buf, get_environ()->argv[*(*s)++ - '0'], -1, symbols);
		return ;
	}
	else if (**s == '?' || **s == '$')
	{
		tmp = ft_itoa(*(*s)++ == '?' ? get_environ()->st
					: get_environ()->sh_pid);
		ft_putstr_mshbuf(buf, tmp, -1);
	}
	else
	{
		tmp = *s;
		while (ft_isword(**s))
			++(*s);
		tmp = ft_strsub(tmp, 0, *s - tmp);
		ft_putstrq_mshbuf(buf, ft_getenv(tmp), -1, symbols);
	}
	free(tmp);
}

static void	record_bslash(t_buf **buf, char **s)
{
	if (!s || !*s || !**s)
		return ;
	if (*(*s + 1) == '\n')
	{
		*s += 2;
		return ;
	}
	ft_putchar_mshbuf(buf, *(*s)++);
	**s ? ft_putchar_mshbuf(buf, *(*s)++) : 0;
}

static void	record_quote(t_buf **buf, char **s)
{
	char	*st;

	if (!s || !*s)
		return ;
	st = (*s)++;
	while (**s && **s != '\'')
		++(*s);
	ft_putstr_mshbuf(buf, st, *s - st + 1);
	**s ? (*s)++ : 0;
}

static void	record_dquote(t_buf **buf, char **s)
{
	ft_putchar_mshbuf(buf, *(*s)++);
	while (**s != '"' && **s)
		if (**s == '\\')
			record_bslash(buf, s);
		else if (**s == '`' || (**s == '$' && *(*s + 1) == '('))
			substitute_cmd(buf, s, "\"\\");
		else if (**s == '$' && ft_isvar(*(*s + 1)) && (*s)++)
			record_var(buf, s, "\"\\");
		else
			ft_putchar_mshbuf(buf, *(*s)++);
	**s ? ft_putchar_mshbuf(buf, *(*s)++) : 0;
}

void		substitute_variable(t_list *lst)
{
	char	*s;
	t_buf	*buf;
	t_buf	*head;

	s = lst->content;
	if (!(buf = ft_memalloc(sizeof(t_buf))))
		return ;
	head = buf;
	expand_tilde(&buf, &s);
	while (*s)
		if (*s == '\\')
			record_bslash(&buf, &s);
		else if (*s == '$' && ft_isvar(*(s + 1)) && s++)
			record_var(&buf, &s, "'\"\\");
		else if (*s == '`' || (*s == '$' && *(s + 1) == '('))
			substitute_cmd(&buf, &s, "'\"\\");
		else if (*s == '\'' || *s == '"')
			*s == '"' ? record_dquote(&buf, &s) : record_quote(&buf, &s);
		else
			ft_putchar_mshbuf(&buf, *s++);
	free(lst->content);
	lst->content = ft_buftostr(head);
}
