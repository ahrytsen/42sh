/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_un_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:33:37 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/08 13:33:39 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_unsetenv(char **av)
{
	int	ret;

	ret = 0;
	if (!av)
		return (256);
	while (*av)
		if (ft_unset_tool(*av++, ENVAR))
			ret = 256;
	return (ret);
}

int		ft_setenv(char **av)
{
	char	*value;
	int		i;
	int		ret;

	ret = 0;
	if (!av)
		return (256);
	if (!*av)
		ft_env_op(ENV_PRINT);
	while (*av)
	{
		if ((value = ft_strchr(*av, '=')))
			*value++ = '\0';
		i = -1;
		while ((*av)[++i])
			if (((i && !ft_isalnum((*av)[i])) || (!i && !ft_isalpha((*av)[i])))
			&& (*av)[i] != '_'
			&& ft_dprintf(2, "setenv: `%s': not a valid identifier\n", *av))
				return (256);
		if (ft_set_tool(*av++, value, 1, ENVAR))
			ret = 256;
	}
	return (ret);
}
