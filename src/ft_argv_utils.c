/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:25:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/31 02:22:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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
