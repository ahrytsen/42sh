/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:56:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/30 23:46:22 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

/*char		*record_var(t_buf **buf, char *s)
{
	char	*tmp;

	tmp = NULL;
	if (ft_isdigit(*s) && *s - 48 <= get_environ()->argc)
		ft_putstr_mshbuf(buf, get_environ()->argv[*s++ - 48], -1);
	else if (*s == '?' && ++s)
	{
		tmp = ft_itoa(get_environ()->st);
		ft_putstr_mshbuf(buf, tmp, -1);
	}
	else if (*s == '$' && ++s)
	{
		tmp = ft_itoa(get_environ()->sh_pid);
		ft_putstr_mshbuf(buf, tmp, -1);
	}
	else
	{
		tmp = s;
		while (ft_isword(*s))
			++s;
		tmp = ft_strsub(tmp, 0, s - tmp);
		ft_putstr_mshbuf(buf, ft_getenv(tmp), -1);
	}
	free(tmp);
	return (s);
}

static char	*record_quote(char *s, t_buf **buf)
{
	char	*st;
	char	quote;

	st = s;
	quote = *s++;
	while (*s != '\'')
	{
		if (!*s)
			break ;
		if (*s == '\\' && quote == '`')
			++s;
		++s;
	}
	ft_putstr_mshbuf(buf, st, s - st + 1);
	return (*s ? ++s : s);
}

static char	*skip_parentheses(char *s, t_buf **buf)
{
	if (*s == '$')
		ft_putchar_mshbuf(buf, *s++);
	ft_putchar_mshbuf(buf, *s++);
	while (*s)
		if (*s == '\\')
		{
			ft_putchar_mshbuf(buf, *s++);
			*s ? ft_putchar_mshbuf(buf, *s++) : 0;
		}
		else if (*s && ft_strchr("\"'`", *s))
			s = record_quote(s, buf);
		else if (*s == ')')
			break ;
		else if (*s == '(')
			s = skip_parentheses(s, buf);
		else
			ft_putchar_mshbuf(buf, *s++);
	ft_putchar_mshbuf(buf, *s++);
	return (s);
}

static char	*record_dquote(char *s, t_buf **buf)
{
	ft_putchar_mshbuf(buf, *s++);
	while (*s != '"' && *s)
		if (*s == '\\')
		{
			ft_putchar_mshbuf(buf, *s++);
			*s ? ft_putchar_mshbuf(buf, *s++) : 0;
		}
		else if (*s == '$' && *(s + 1) == '(')
			s = skip_parentheses(s, buf);
		else if (*s == '$' && ft_isword(*(s + 1)) && s++)
			s = record_var(buf, s);
		else
			ft_putchar_mshbuf(buf, *s++);
	ft_putchar_mshbuf(buf, *s++);
	return (s);
}
*/
void		substitute_cmd(t_list *lst)
{
/*	char	*s;
	t_buf	*buf;
	t_buf	*head;

	s = lst->content;
	buf = ft_memalloc(sizeof(t_buf));
	head = buf;
	while (*s)
		if (*s == '\\')
		{
			ft_putchar_mshbuf(&buf, *s++);
			*s ? ft_putchar_mshbuf(&buf, *s++) : 0;
		}
		else if (*s == '$' && *(s + 1) == '(')
			s = skip_parentheses(s, &buf);
		else if (*s && ft_strchr("\"'`", *s))
			s = (*s == '"' ? record_dquote(s, &buf) : record_quote(s, &buf));
			else
			ft_putchar_mshbuf(&buf, *s++);
	free(lst->content);
	lst->content = ft_buftostr(head);*/
	(void)lst;
}
