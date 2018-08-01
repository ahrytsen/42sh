/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 13:02:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:21:02 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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
