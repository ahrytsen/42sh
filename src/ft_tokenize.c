/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:11:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/13 21:29:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_get_redirect_in(char **ln, t_token *token)
{
	if (**ln == '<' && !(*(*ln)++ = '\0'))
	{
		if (**ln == '<' && !(*(*ln)++ = '\0'))
			token->type = herestr;
		else if (**ln == '-' && !(*(*ln)++ = '\0'))
			token->type = heredoc_t;
		else
			token->type = heredoc;
	}
	else if (**ln == '>' && !(*(*ln)++ = '\0'))
		token->type = open_file;
	else if (**ln == '&' && !(*(*ln)++ = '\0'))
		token->type = read_in_and;
	else
		token->type = read_in;
}

static void	ft_get_redirect_out(char **ln, t_token *token)
{
	if (**ln == '|' && !(*(*ln)++ = 0))
		token->type = read_out_pipe;
	else if (**ln == '&' && !(*(*ln)++ = 0))
		token->type = read_out_and;
	else if (**ln == '>' && !(*(*ln)++ = 0))
		token->type = read_out_apend;
	else
		token->type = read_out;
}

static int	ft_get_separator(char **ln, t_token *token)
{
	if ((**ln == ' ' || **ln == '\t') && !(*(*ln)++ = '\0'))
		token->type = blank;
	else if ((**ln == ';' && (token->type = semi))
			|| (**ln == '\n' && (token->type = nl)))
		*(*ln)++ = '\0';
	else if (**ln == '|' && !(*(*ln)++ = '\0'))
		token->type =
			(**ln == '|' && !(*(*ln)++ = '\0')) ? or : pipeline;
	else if (**ln == '&' && !(*(*ln)++ = '\0'))
	{
		if (**ln == '>' && !(*(*ln)++ = '\0'))
			token->type = and_read_out;
		else
			token->type =
				(**ln == '&' && !(*(*ln)++ = '\0')) ? and : bg_op;
	}
	else if ((**ln == '(' || **ln == ')') && (token->type = subsh))
		return (ft_get_subsh(ln, token));
	else if (**ln == '<' && !(*(*ln)++ = '\0')
			&& !(token->data.redir.left = 0))
		ft_get_redirect_in(ln, token);
	else if (**ln == '>' && !(*(*ln)++ = '\0')
			&& (token->data.redir.left = 1))
		ft_get_redirect_out(ln, token);
	return (0);
}

static int	ft_get_token(char **ln, t_token *token)
{
	token->type = word;
	token->data.word = *ln;
	if (ft_skip_word(ln))
		return (1);
	if ((**ln == '<' || **ln == '>')
		&& ft_isnumeric_n(token->data.word, *ln - token->data.word))
	{
		token->data.redir.left = ft_atoi(token->data.word);
		token->data.redir.cls = 0;
		(**ln == '<' && (*ln)++) || !++(*ln) ? ft_get_redirect_in(ln, token)
			: ft_get_redirect_out(ln, token);
	}
	return (0);
}

t_list		*ft_tokenize(char *ln)
{
	t_token	tok;
	t_list	*toks;
	t_list	*tmp;

	toks = NULL;
	while (*ln)
	{
		ft_bzero(&tok, sizeof(tok));
		if ((!ft_isseparator(*ln) ? ft_get_token : ft_get_separator)(&ln, &tok))
			ft_lstdel(&toks, ft_token_del);
		else if ((tok.type == nl && ((!toks || ft_isoperator(tmp->content))
				|| !(tok.type = semi))) || tok.type == blank)
			continue ;
		else if (toks && ((t_token*)tmp->content)->type > or
			&& !((t_token*)tmp->content)->data.redir.right && tok.type == word)
			((t_token*)tmp->content)->data.redir.right = tok.data.word;
		else if (ft_redir_check(toks ? tmp->content : NULL, &tok, ln)
			|| !(tmp = ft_lstpush_back(toks ? &tmp : &toks, &tok, sizeof(tok))))
		{
			!tmp ? write(2, "42sh: malloc error\n", 19) : 0;
			ft_lstdel(&toks, ft_token_del);
			return (NULL);
		}
	}
	return (toks);
}
