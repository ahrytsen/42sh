/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:11:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/04 20:56:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_get_redirect_in(char **ln, t_token *token)
{
	*(*ln)++ = '\0';
	token->type = redir;
	token->data.redir.left = 0;
	if (**ln == '<' && !(*(*ln)++ = '\0'))
	{
		if (**ln == '<' && !(*(*ln)++ = '\0'))
			token->data.redir.type = herestr;
		else if (**ln == '-' && !(*(*ln)++ = '\0'))
			token->data.redir.type = heredoc_t;
		else
			token->data.redir.type = heredoc;
	}
	else if (**ln == '>' && !(*(*ln)++ = '\0'))
		token->data.redir.type = open_file;
	else if (**ln == '&' && !(*(*ln)++ = '\0'))
		token->data.redir.type = read_in_and;
	else
		token->data.redir.type = read_in;
}

static void	ft_get_redirect_out(char **ln, t_token *token)
{
	*(*ln)++ = '\0';
	token->type = redir;
	token->data.redir.left = 1;
	if (**ln == '|' && !(*(*ln)++ = 0))
		token->data.redir.type = read_out_pipe;
	else if (**ln == '&' && !(*(*ln)++ = 0))
		token->data.redir.type = read_out_and;
	else if (**ln == '>' && !(*(*ln)++ = 0))
		token->data.redir.type = read_out_apend;
	else
		token->data.redir.type = read_out;
}

static int	ft_get_separator(char **ln, t_token *token)
{
	if ((**ln == ' ' || **ln == '\t') && !(*(*ln)++ = '\0'))
		token->type = blank;
	else if ((**ln == ';' && (token->type = semi)))
		*(*ln)++ = '\0';
	else if (**ln == '\n' && (token->type = nl))
		*(*ln)++ = '\0';
	else if (**ln == '|' && !(*(*ln)++ = '\0'))
		token->type =
			(**ln == '|' && !(*(*ln)++ = '\0')) ? or : pipeln;
	else if (**ln == '&')
		ft_get_ampersand(ln, token);
	else if ((**ln == '(' || **ln == ')') && (token->type = subsh))
		return (ft_get_subsh(ln, token));
	else if (**ln == '<')
		ft_get_redirect_in(ln, token);
	else if (**ln == '>')
		ft_get_redirect_out(ln, token);
	return (0);
}

static int	ft_get_token(char **ln, t_token *token)
{
	char	*tmp;

	token->type = word;
	token->word = *ln;
	if (ft_skip_word(ln))
		return (1);
	if ((**ln == '<' || **ln == '>')
		&& ft_isnumeric_n(token->word, *ln - token->word))
	{
		(**ln == '<' ? ft_get_redirect_in : ft_get_redirect_out)(ln, token);
		token->data.redir.left = ft_atoi(token->word);
		token->word = NULL;
	}
	else if ((tmp = ft_strsub(token->word, 0, *ln - token->word)))
		token->word = tmp;
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
		else if (toks && ((t_token*)tmp->content)->type == redir
			&& !((t_token*)tmp->content)->word && tok.type == word)
			((t_token*)tmp->content)->word = tok.word;
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
