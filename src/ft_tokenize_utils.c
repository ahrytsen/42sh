/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:11:31 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/05 17:58:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_get_subsh(char **ln, t_token *token)
{
	t_list	*toks;

	toks = NULL;
	if (**ln == ')' && !(**ln = '\0')
		&& write(2, "42sh: syntax error near unexpected token `)'\n", 45))
		return (1);
	**ln = '\0';
	token->word = *ln + 1;
	if (ft_skip_subsh(ln))
		return (1);
	*(*ln - 1) = '\0';
	if (!(toks = ft_tokenize(token->word))
		|| !ft_heredoc(toks)
		|| (!(token->data.sub_ast = ft_ast_make(&toks))
			&& write(2, "42sh: syntax error near unexpected token `)'\n", 45)))
	{
		ft_lstdel(&toks, ft_token_del);
		return (1);
	}
	token->word = NULL;
	ft_lstdel(&toks, ft_token_del);
	return (0);
}

int		ft_skip_word(char **ln)
{
	while (**ln && !ft_isseparator(**ln))
		if (**ln == '\'' || **ln == '"' || **ln == '`')
		{
			if (ft_skip_quotes(ln))
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
			&& ft_dprintf(2, "42sh: syntax error: %s `)'\n",
						"unexpected EOF while looking for matching"))
			return (1);
		else if (**ln == '\'' || **ln == '`' || **ln == '"')
		{
			if (ft_skip_quotes(ln))
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

int		ft_skip_quotes(char **ln)
{
	char	q;

	q = *(*ln)++;
	while (**ln != q)
		if (!**ln
			&& ft_dprintf(2, "42sh: syntax error: %s `%c'\n",
						"unexpected EOF while looking for matching", q))
			return (1);
		else if (q == '"' && **ln == '`')
			ft_skip_quotes(ln);
		else if (q != '\'' && **ln == '\\')
			*++(*ln) ? (*ln)++ : 0;
		else if (q == '"' && **ln == '$' && *((*ln) + 1) == '(' && (*ln)++)
		{
			if (ft_skip_subsh(ln))
				return (1);
		}
		else
			(*ln)++;
	(*ln)++;
	return (0);
}
