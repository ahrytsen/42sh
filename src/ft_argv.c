/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:02:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/25 01:18:59 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_expansions.h"

t_list	*get_lst_end(t_list *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstiter_custom(t_list **lst, t_list *(*f)(t_list *))
{
	t_list	*lst_prev;
	t_list	*new_lst;
	t_list	*tmp_lst;
	t_list	*new_lst_end;

	lst_prev = NULL;
	tmp_lst = *lst;
	while (tmp_lst)
	{
		if ((new_lst = (*f)(tmp_lst)))
		{
			new_lst_end = get_lst_end(new_lst);
			lst_prev ? (lst_prev->next = tmp_lst->next) : (*lst = tmp_lst->next);
			ft_lstdelone(&tmp_lst, (void (*)(void *, size_t))free);
			ft_lstinsert(lst, lst_prev, new_lst);
			tmp_lst = new_lst_end;
		}
		lst_prev = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
}

t_list	*perform_expansions(t_list *toks)
{
	t_list	*lst;

	lst = NULL;
	while (toks)
	{
		if (((t_token*)(toks->content))->type == word)
					ft_lstpush_back(&lst, ((t_token*)(toks->content))->word,
							ft_strlen(((t_token*)(toks->content))->word) + 1);
						toks = toks->next;
	}
	lstiter_custom(&lst, brace_expansion);
	ft_lstiter(lst, expand_tilde);
	ft_lstiter(lst, substitute_variable);

	// Command Substitution

	lstiter_custom(&lst, expand_pathname);
	ft_lstiter(lst, remove_quotes);
	return (lst);
}

char	**ft_argv_make(t_list *toks)
{
	int		i;
	char	**av;
	t_list	*lst;
	t_list	*tmp;

	lst = perform_expansions(toks);
	tmp = lst;
	i = ft_lstsize(lst) + 1;
	if (!(av = ft_memalloc(i * sizeof(av))))
		return (NULL);
	i = 0;
	while (lst)
	{
		av[i++] = lst->content;
		lst = lst->next;
	}
	ft_lstdel(&tmp, NULL);
	tmp = NULL;
	return (av);
}
