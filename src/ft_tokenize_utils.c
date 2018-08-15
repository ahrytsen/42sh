/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:11:31 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/15 22:05:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const char	*ft_tname(t_token *tok)
{
	static const char *const	t_names[] =
		{
			" ", "redir", "word", "res_word", "|", "(", ")",
			"&", "newline", ";", ";;", "&&", "||"
		};
	static const char *const	r_names[] =
		{
			"<<", "<<-", "<<<", "<>", ">", ">|", ">>", "<", "<&", ">&", "&>"
		};

	if (!tok)
		return ("newline");
	else if (tok->type == redir && tok->data.redir.type >= heredoc
			&& tok->data.redir.type <= and_read_out)
		return (r_names[tok->data.redir.type]);
	else if (tok->type == word || tok->type == res_word)
		return (tok->data.word);
	else if (tok->type >= blank && tok->type <= or)
		return (t_names[tok->type]);
	else
		return ("unknown token");
}

void	ft_token_del(void *token, size_t size)
{
	(void)size;
	if (((t_token*)token)->type >= heredoc
		&& ((t_token*)token)->type <= herestr)
		free(((t_token*)token)->data.redir.hd);
	free(token);
}

int		ft_isseparator(int c)
{
	return (ft_strchr("|&;()<> \t\n", c) ? 1 : 0);
}

int		ft_skip_word(char **ln)
{
	while (**ln && !ft_isseparator(**ln))
		if (**ln == '\'' || **ln == '"' || **ln == '`')
		{
			if (ft_skip_qoutes(ln))
				return (1);
		}
		else if (*(*ln) == '$' && *((*ln) + 1) == '(' && (*ln)++)
		{
			if (ft_skip_subsh(ln))
				return (1);
		}
		else if (**ln == '\\')
			*++(*ln) ? (*ln)++ : 0;
		else
			(*ln)++;
	return (0);
}

int		ft_skip_subsh(char **ln)
{
	(*ln)++;
	while (**ln != ')')
		if (!**ln
			&& ft_dprintf(2, "42sh: %s `)'\n",
						"unexpected EOF while looking for matching"))
			return (1);
		else if (**ln == '\'' || **ln == '`' || **ln == '"')
		{
			if (ft_skip_qoutes(ln))
				return (1);
		}
		else if (**ln == '(')
		{
			if (ft_skip_subsh(ln))
				return (1);
		}
		else if (**ln == '\\')
			*++(*ln) ? (*ln)++ : 0;
		else
			(*ln)++;
	(*ln)++;
	return (0);
}

int		ft_skip_qoutes(char **ln)
{
	char	q;

	q = *(*ln)++;
	while (**ln != q)
		if (!**ln
			&& ft_dprintf(2, "42sh: %s `%c'\n",
						"unexpected EOF while looking for matching", q))
			return (1);
		else if (q == '"' && **ln == '`')
			ft_skip_qoutes(ln);
		else if (q != '\'' && **ln == '\\')
			*++(*ln) ? (*ln)++ : 0;
		else if (q != '\'' && **ln == '$' && *((*ln) + 1) == '(' && (*ln)++)
		{
			if (ft_skip_subsh(ln))
				return (1);
		}
		else
			(*ln)++;
	(*ln)++;
	return (0);
}
