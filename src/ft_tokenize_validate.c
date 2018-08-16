/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 18:55:41 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/16 18:49:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"



static int	check_token(t_token *prev, t_token *cur)
{
	{word, pipeline, subsh_on, bg_op, semi, dsemi, } -> word
	if (cur->type == word)
	{

	}
	else if (cur->type == subsh_on || cur->type == subsh_off)
	{

	}
	else
	{

	}
}

void	ft_check_res_word(t_token *tok)
{

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
						ft_tname(tok)))
			return (0);
		if (check_token(prev ? prev->content : NULL, tok))
			return (0);
		toks = toks->next;
	}
	return (1);
}
