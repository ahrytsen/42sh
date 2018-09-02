/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:56:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/01 14:50:09 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"
/*
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

char		*ft_get_parentheses_cmd(t_buf **cur, char *s)
{

}

char		*ft_get_bquote_cmd(t_buf **cur, char **line)
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