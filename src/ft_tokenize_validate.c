/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:55:41 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/14 21:48:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		*ft_tname(int type)
{
	if (!type)
		return ("newline");
	else if (type == pipeline || type == bg_op)
		return (type == pipeline ? "|" : "&");
	else if (type == semi || type == and)
		return (type == semi ? ";" : "&&");
	else if (type == or || type == heredoc)
		return (type == or ? "||" : "<<");
	else if (type == heredoc_t || type == herestr)
		return (type == heredoc_t ? "<<-" : "<<<");
	else if (type == open_file || type == read_out)
		return (type == open_file ? "<>" : ">");
	else if (type == read_out_pipe || type == read_out_apend)
		return (type == read_out_pipe ? ">|" : ">>");
	else if (type == read_in || type == read_in_and)
		return (type == read_in ? "<" : "<&");
	else if (type == read_out_and || type == and_read_out)
		return (type == read_out_and ? ">&" : "&>");
	else if (type == subsh_on || type == subsh_off)
		return (type == subsh_on ? "(" : ")");
	else
		return ("?");
}

static int	check_token(t_token *prev, t_token *cur)
{
	if (cur->type == word )
}

int		ft_tokenize_validate(t_list *toks)
{
	int		subsh;
	t_token	*tok;
	t_list	*prev;

	subsh = 0;
	prev = NULL;
	tok = NULL;
	while (toks)
	{
		tok = toks->content;
		tok && tok->type == subsh_on ? (subsh++) : 0;
		if (tok && tok->type == subsh_off && !(subsh--)
			&& ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n",
						ft_tname(tok->type)))
			return (0);
		if (check_token(prev ? prev->content, tok))
			return (0);
		toks = toks->next;
	}
	return (1);
}
