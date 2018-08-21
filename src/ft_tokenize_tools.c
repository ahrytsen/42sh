/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 20:36:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/21 20:25:42 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_token_del(void *token, size_t size)
{
	t_token	*tok;

	tok = token;
	(void)size;
	if (tok->type == redir)
	{
		if (tok->data.redir.type >= heredoc
			&& tok->data.redir.type <= herestr)
			free(tok->data.redir.hd);
		free(tok->data.redir.right);
	}
	else if (tok->type == subsh)
		ft_ast_del(tok->data.sub_ast, 1);
	free(tok->word);
	free(tok);
}

int			ft_isseparator(int c)
{
	return (ft_strchr("|&;()<> \t\n", c) ? 1 : 0);
}

const char	*ft_tname(t_token *tok)
{
	static const char *const	t_names[] = {
		" ", "redir", "assignment", "word", "res_word", "|", "(",
		"newline", "&", ";", ";;", "&&", "||"};
	static const char *const	r_names[] = {
		"<<", "<<-", "<<<", "<>", ">", ">|", ">>", "<", "<&", ">&", "&>"};

	if (!tok)
		return ("newline");
	else if (tok->type == redir && tok->data.redir.type >= heredoc
			&& tok->data.redir.type <= and_read_out)
		return (r_names[tok->data.redir.type]);
	else if (tok->type == word || tok->type == res_word
			|| tok->type == assignment)
		return (tok->word);
	else if (tok->type >= blank && tok->type <= or)
		return (t_names[tok->type]);
	else
		return ("unknown token");
}
