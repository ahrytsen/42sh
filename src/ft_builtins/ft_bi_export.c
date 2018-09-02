/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:00:23 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/28 18:28:29 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_read_export_flags(char ***av, int *flags)
{
	int i;

	i = 0;
	*flags = 0;
	if (**av && (**av)[i] == '-')
	{
		i++;
		while ((**av)[i])
		{
			if ((**av)[i] != 'n' && (**av)[i] != 'o' && (**av)[i] != 'p')
			{
				ft_dprintf(2, "export: illegal option: -%c\n", (**av)[i]);
				write(2, "export: usage: export [-nop] [name[=value]]\n", 43);
				return (1);
			}
			if ((**av)[i] != 'p')
				*flags |= ((**av)[i] - 109);
			else
				*flags |= 4;
			i++;
		}
		(*av)++;
	}
	return (0);
}

static void	ft_kick_env_var(const char *name)
{
	char	**env;

	env = get_environ()->envar;
	if (!env || !name || ft_strchr(name, '='))
		return ;
	while (*env && ft_strcmp(*env, name) != '=')
		env++;
	if (!*env)
		return ;
	free(*env);
	while (*env++)
		*(env - 1) = *env;
}

static void	ft_export_part_two(char *str, char *value, t_var *entry, int flags)
{
	if (entry)
	{
		if (flags & 1 && entry->attr == 'e')
		{
			entry->attr = 'l';
			ft_kick_env_var(str);
		}
		else if (flags & 2 && (entry->attr == 'e' || entry->attr == 'u'))
			ft_putendl(entry->var);
		else if (entry->attr != 'u')
		{
			if (value)
				ft_set_tool(str, value, 1, ENVAR);
			else if (entry->attr != 'e')
			{
				entry->attr = 'e';
				ft_setter(str, ft_strchr(entry->var, '=') + 1);
			}
		}
	}
	else if (value)
		ft_set_tool(str, value, 1, ENVAR);
	else
		ft_set_tool(str, NULL, 1, -1);
}

int			ft_export(char **av)
{
	char	*value;
	int		flags;
	int		rat;

	rat = 0;
	if (ft_read_export_flags(&av, &flags))
		return (256);
	if (!*av)
		return (ft_print_shvar(flags));
	while (*av)
	{
		if (!ft_is_valid_name(*av))
		{
			ft_dprintf(2, "42sh: export: %s is not a valid identifier\n", *av);
			rat = 1;
			av++;
			continue ;
		}
		if ((value = ft_strchr(*av, '=')))
			*value++ = '\0';
		ft_export_part_two(*av, value, ft_get_shvar_entry(*av), flags);
		av++;
	}
	return (rat);
}
