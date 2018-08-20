/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:02:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/20 17:48:22 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_lstreplace(t_list *lst1, t_list *lst2)
{
	t_list	*lst
}

void	ft_lstiter_custom(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_next;
	t_list	*lst_prev;
	t_list	*new_lst;

	lst_prev = NULL;
	while (lst && f)
	{
		lst_next = lst->next;
		if ((new_lst = (*f)(lst)))
		{
			//delete node from lst
			ft_lstinsert(lst_prev, new_lst);
		}
		lst_prev = lst;
		lst = lst_next;
	}
}

void	perform_expansions(t_list *toks)
{
	t_list	*lst;

	while (tok)
	{
		if (((t_token*)(toks->content))->type == word)
			ft_lstpush_back(&lst, ((t_token*)(toks->content))->data.word,
						ft_strlen(((t_token*)(toks->content))->data.word) + 1);
		toks = toks->next;
	}
	ft_lstiter_custom(lst, )
}

int		ft_count_args(t_list *toks)
{
	int	ret;

	ret = 0;
	while (toks)
	{
		if (((t_token*)(toks->content))->type == word)
			ret++;
		toks = toks->next;
	}
	return (ret);
}

char	**ft_argv_make(t_list *toks)
{
	int		i;
	int		size;
	char	**av;

	i = 0;
	size = ft_count_args(toks) + 1;
	if (!(av = ft_memalloc(size * sizeof(av))))
		return (NULL);
	while (i < size && toks)
	{
		if (((t_token*)(toks->content))->type == word
			&& !(av[i++] = parse_argv(((t_token*)(toks->content))->data.word)))
		{
			ft_strarr_free(av);
			return (NULL);
		}
		toks = toks->next;
	}
	return (av);
}
