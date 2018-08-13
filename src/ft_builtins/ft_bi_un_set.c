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

int			ft_print_shvar(int mod)
{
	t_var *env;

	env = get_environ()->shvar;
	while (env)
	{
		if ((mod < ENVAR && env->attr == 'l')
		|| (mod > SHVAR && env->attr == 'e'))
			ft_printf("%c %s\n", env->attr, env->var);
		env = env->next;
	}
	return (0);
}

int		ft_set(char **av)
{
	// char	*value;
	// int		i;
	int		ret;

	ret = 0;
	if (!av)
		return (256);
	if (!*av || !ft_strcmp(*av, "--"))
		ft_print_shvar(1);
	// while (*av)
	// {
	// 	if ((value = ft_strchr(*av, '=')))
	// 		*value++ = '\0';
	// 	i = -1;
	// 	while ((*av)[++i])
	// 		if (((i && !ft_isalnum((*av)[i])) || (!i && !ft_isalpha((*av)[i])))
	// 		&& (*av)[i] != '_'
	// 		&& ft_dprintf(2, "set: `%s': not a valid identifier\n", *av + 1))
	// 			return (256);
	// 	if (ft_set_tool(*av++, value, 1, SHVAR))
	// 		ret = 256;
	// }
	return (ret);
}
