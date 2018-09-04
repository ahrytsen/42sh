/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_unalias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:46:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/04 20:16:45 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_unalias_usage(void)
{
	ft_dprintf(2, "unalias: usage: unalias name [name ...]\n");
	return (256);
}

static int	ft_unalias_byname(char *name)
{
	t_alias	**alias;
	t_alias	*tmp;

	alias = ft_get_alias(name);
	if (alias && *alias)
	{
		tmp = (*alias)->next;
		free((*alias)->name);
		free((*alias)->value);
		free(*alias);
		*alias = tmp;
		return (0);
	}
	ft_dprintf(2, "unalias: %s: not found\n", name);
	return (1);
}

int			ft_unalias(char **av)
{
	int	ret;

	ret = 0;
	if (!av || !*av)
		return (ft_unalias_usage());
	while (*av)
		ft_unalias_byname(*av++) ? (ret = 256) : 0;
	return (ret);
}
