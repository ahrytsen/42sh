/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:56:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/05 20:38:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

static void	ft_bquote_child(int fd_get[2], char *cmds)
{
	t_list	*toks;
	t_ast	*ast;

	signal(SIGINT, SIG_DFL);
	get_environ()->is_interactive = 0;
	close(fd_get[0]);
	dup2(fd_get[1], 1);
	ft_fildes(FD_BACKUP);
	if ((toks = ft_tokenize(cmds)) && ft_heredoc(toks))
	{
		ast = ft_ast_make(&toks);
		get_environ()->st = ft_ast_exec(ast);
		ast = ft_ast_del(ast, 1);
	}
	ft_lstdel(&toks, ft_token_del);
	free(cmds);
	close(fd_get[1]);
	exit(get_environ()->st);
}

static void	ft_bquote_helper(t_buf **cur, char *str, char *symbols)
{
	int		fd_get[2];
	char	*line;

	pipe(fd_get);
	if ((get_environ()->pid = fork()))
	{
		close(fd_get[1]);
		if ((line = ft_read_cmdsubst(fd_get[0])))
		{
			ft_putstrq_mshbuf(cur, line, -1, symbols);
			free(line);
		}
		close(fd_get[0]);
		waitpid(get_environ()->pid, &get_environ()->st, 0);
		get_environ()->st = WEXITSTATUS(get_environ()->st);
		get_environ()->pid = 0;
		tcsetpgrp(get_environ()->sh_terminal, get_environ()->sh_pgid);
	}
	else if (get_environ()->pid == -1)
		write(2, "42sh: fork() error\n", 19);
	else
		ft_bquote_child(fd_get, str);
}

static char	*get_prnth_cmd(char **s)
{
	char	*st;

	st = ++(*s);
	st++;
	if (ft_skip_subsh(s))
		return (NULL);
	return (ft_strsub(st, 0, *s - st - 1));
}

static char	*get_bq_cmd(char **s)
{
	t_buf	*head;
	t_buf	*tmp;
	char	*st;

	if (!s || !*s)
		return (NULL);
	st = *s + 1;
	if (ft_skip_quotes(s)
		|| !(head = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	tmp = head;
	while (st < *s - 1)
		if (*st == '\\')
			ft_putchar_mshbuf(&tmp, *st && ft_strchr("\\$`", *(st + 1))
							? *++st : *st++);
		else
			ft_putchar_mshbuf(&tmp, *st++);
	return (ft_buftostr(head));
}

void		substitute_cmd(t_buf **buf, char **s, char *symbols)
{
	char	*cmd;
	char	*st;

	st = *s;
	if (!(cmd = (**s == '$' ? get_prnth_cmd : get_bq_cmd)(s)))
	{
		ft_putstr_mshbuf(buf, st, -1);
		return ;
	}
	if (*cmd)
		ft_bquote_helper(buf, cmd, symbols);
	free(cmd);
}
