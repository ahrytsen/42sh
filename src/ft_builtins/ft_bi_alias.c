/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 16:45:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/04 21:02:25 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_alias_print(char *name)
{
	t_alias	*aliases;

	aliases = get_environ()->aliases;
	while (aliases)
	{
		if (!name || ft_strequ(aliases->name, name))
		{
			ft_printf("%s=%s\n", aliases->name, aliases->value);
			if (name)
				break ;
		}
		aliases = aliases->next;
	}
	if (!aliases && name && ft_dprintf(2, "alias: %s: not found\n", name))
		return (1);
	return (0);
}

t_alias		**ft_get_alias(char *name)
{
	t_alias	**alias;

	alias = &get_environ()->aliases;
	while (*alias && !ft_strequ((*alias)->name, name))
		alias = &(*alias)->next;
	return (alias);
}

int			ft_alias(char **av)
{
	int		ret;
	t_alias	**alias;
	char	*tmp;

	if (!(ret = 0) && (!av || !*av))
		return (ft_alias_print(NULL) ? 256 : 0);
	while (*av)
	{
		if ((tmp = ft_strchr(*av, '=')))
		{
			*tmp++ = '\0';
			alias = ft_get_alias(*av);
			if (!*alias && !(*alias = ft_memalloc(sizeof(t_alias)))
				&& ft_dprintf(2, "alias: malloc error\n"))
				return (256);
			free((*alias)->name);
			(*alias)->name = ft_strdup(*av);
			free((*alias)->value);
			(*alias)->value = ft_strdup(tmp);
		}
		else
			ft_alias_print(*av) ? (ret = 256) : 0;
		av++;
	}
	return (ret);
}
