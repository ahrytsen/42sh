/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 08:15:32 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/25 06:19:53 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

static char	*record_var(t_buf **buf, char *s)
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
	else if  (*s == '$' && ++s)
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
	char	*tmp;

	tmp = ft_strchr(s + 1, *s);
	ft_putstr_mshbuf(buf, s, tmp - s + 1);
	return (tmp + 1);
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
		else if (*s == '$' && ft_isword(*(s + 1)) && s++)
			s = record_var(buf, s);
		else
			ft_putchar_mshbuf(buf, *s++);
	ft_putchar_mshbuf(buf, *s++);
	return (s);
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

void	substitute_variable(t_list *lst)
{
	char	*s;
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
		else if (*s == '$' && ft_isword(*(s + 1)) && s++)
			s = record_var(&buf, s);
		else if (*s == '$' && *(s + 1) == '(')
			s = skip_parentheses(s, &buf);
		else if (*s == '"')
			s = record_dquote(s, &buf);
		else if (*s == '\'' || *s == '`')
			s = record_quote(s, &buf);
		else
			ft_putchar_mshbuf(&buf, *s++);
	free(lst->content);
	lst->content = ft_buftostr(head);
}
