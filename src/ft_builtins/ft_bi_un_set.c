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
