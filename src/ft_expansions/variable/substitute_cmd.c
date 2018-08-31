/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:56:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/31 05:11:07 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

static void	ft_bquote_child(int fd_get[2], char *cmds)
{
	t_list	*toks;
	t_ast	*ast;

	get_environ()->pid = 1;
	close(fd_get[0]);
	dup2(fd_get[1], 1);
	toks = ft_tokenize(cmds);
	ast = ft_ast_make(&toks);
	ft_lstdel(&toks, ft_token_del);
	get_environ()->st = ft_ast_exec(ast);
	ast = ft_ast_del(ast, 1);
	free(cmds);
	close(fd_get[1]);
	exit(get_environ()->st);
}

static void	ft_bquote_helper(t_buf **cur, char *str)
{
	int		fd_get[2];
	char	*line;
	int		i;

	i = 0;
	pipe(fd_get);
	if ((get_environ()->pid = fork()))
	{
		close(fd_get[1]);
		while (get_next_line(fd_get[0], &line) > 0)
		{
			i++ ? ft_putchar_mshbuf(cur, '\n') : 0;
			ft_putstr_mshbuf(cur, line, -1);
			free(line);
		}
		close(fd_get[0]);
		waitpid(get_environ()->pid, &get_environ()->st, WUNTRACED);
		get_environ()->st = WEXITSTATUS(get_environ()->st);
		get_environ()->pid = 0;
	}
	else if (get_environ()->pid == -1)
		write(2, "42sh: fork() error\n", 19);
	else
		ft_bquote_child(fd_get, str);
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
