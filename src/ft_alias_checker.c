/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:21:40 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/04 20:16:26 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	expand_alias(char **word)
{
	char	*tmp;
	t_alias	**alias;

	alias = ft_get_alias(*word);
	if (alias && *alias && ft_strequ(*word, (*alias)->name))
	{
		tmp = *word;
		if ((*word = ft_strdup((*alias)->value)))
		{
			free(tmp);
			return (1);
		}
		*word = tmp;
	}
	return (0);
}

void		ft_alias_checker(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		if (token && token->type == word && token->word)
		{
			while (expand_alias(&token->word))
				;
			break ;
		}
		lst = lst->next;
	}
}
