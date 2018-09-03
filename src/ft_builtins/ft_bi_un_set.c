/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_un_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:31:36 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/08 13:32:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_unset(char **av)
{
	int	ret;

	ret = 0;
	if (!av)
		return (256);
	while (*av)
		if (ft_unset_tool(*av++, SHVAR))
			ret = 256;
	return (ret);
}

int		ft_set_var(t_list *var, int mod)
{
	char	*value;
	t_var	*ent;

	while (var)
	{
		value = ft_strchr(var->content, '=');
		*value = '\0';
		if (mod == SHVAR)
		{
			if ((ent = ft_get_shvar_entry(var->content)))
			{
				if (ent->attr == 'e' || (ent->attr == 'u' && (ent->attr = 'e')))
					ft_setter(var->content, value + 1);
				free(ent->var);
				*value = '=';
				ent->var = ft_strdup(var->content);
			}
			else
				ft_set_tool(var->content, value + 1, 1, SHVAR);
		}
		else if (mod == ENVAR)
			ft_setter(var->content, value + 1);
		var = var->next;
	}
	return (0);
}
