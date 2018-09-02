/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 19:39:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/28 18:09:33 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_redir_right_param(t_token *tok)
{
	int		count_digits;
	char	*tmp;

	tmp = tok->data.redir.right;
	count_digits = 0;
	while (*tmp)
	{
		if (*tmp == '-' && !tmp[1])
			tok->data.redir.cls = 1;
		else if (!ft_isdigit(*tmp))
			return (0);
		else
			count_digits++;
		tmp++;
	}
	tok->data.redir.nbr = count_digits ? ft_atoi(tok->data.redir.right) : -1;
	return (1);
}

int		ft_redir_check(t_token *prev, t_token *next, char *ln)
{
	if (((prev && prev->type == redir && !prev->word)
			&& ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n",
							ft_tname(next)))
		|| ((next && next->type == redir && !*ln)
			&& ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n",
							ft_tname(NULL))))
		return (1);
	return (0);
}

int		ft_redir_expansion(t_token *tok)
{
	t_list	*tmp;

	tmp = NULL;
	ft_memdel((void**)&tok->data.redir.right);
	if (!ft_lstpush_back(&tmp, tok->word, ft_strlen(tok->word) + 1)
		&& ft_dprintf(2, "42sh: malloc error\n"))
		return (256);
	tmp = perform_expansions(tmp, EXP_STRS);
	if (!tmp || tmp->next)
	{
		ft_dprintf(2, "42sh: %s: ambiguous redirect\n", tok->word);
		ft_lstdel(&tmp, (void (*)(void *, size_t))free);
		return (256);
	}
	tok->data.redir.right = tmp->content;
	ft_lstdel(&tmp, NULL);
	return (0);
}
