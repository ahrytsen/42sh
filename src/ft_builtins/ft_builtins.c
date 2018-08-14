/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:02:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:19:46 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_echo(char **av)
{
	int	i;
	int n;

	i = 0;
	n = 1;
	if (*av && !ft_strcmp(*av, "-n") && ++i)
		n = 0;
	while (av[i])
	{
		ft_printf("%s", av[i++]);
		av[i] ? ft_printf(" ") : 0;
	}
	n ? ft_printf("\n") : 0;
	return (0);
}

int		ft_exit(char **av)
{
	char	*tmp;

	ft_dprintf(2, "exit\n");
	if (av && *av)
	{
		tmp = *av;
		while (*tmp)
			if (!ft_isdigit(*tmp++))
			{
				ft_dprintf(2, "exit: %s: numeric argument required\n", *av);
				exit(-1);
			}
	}
	if (av && *av && *(av + 1))
	{
		write(2, "exit: too many arguments\n", 25);
		return (256);
	}
	exit((av && *av) ? ft_atoi(*av) : get_environ()->st);
}

int		ft_read_export_flags(char ***av, int *flags)
{
	int i;

	i = 0;
	*flags = 0;
	if (**av && (**av)[i] == '-')
	{
		i++;
		while ((**av)[i])
		{
			if ((**av)[i] != 'p' && (**av)[i] != 'n')
			{
				ft_dprintf(2, "export: bad option: -%c\n", (**av)[i]);
				return (1);
			}
			*flags |= ((**av)[i] == 'n' ? 2 : 1);
			i++;
		}
		(*av)++;
	}
	return (0);
}

int		ft_export(char **av)
{
	char	*value;
	t_var	*entry;
	int		flags;

	if (ft_read_export_flags(&av, &flags))
		return (256);
	if (!*av)
		return (ft_print_shvar(ENVAR));
	while (*av)
	{
		if ((value = ft_strchr(*av, '=')))
			*value++='\0';
		if ((entry = ft_get_shvar_entry(*av)))
		{
			if (flags & 2)
				ft_putendl("unexport");
			else if (flags & 1)
				ft_putendl(entry->var);
			else
			{
				if (value)
					ft_set_tool(*av, value, 1, ENVAR);
				else if (entry->attr != 'e')
				{
					entry->attr = 'e';
					ft_setter(*av, ft_strchr(entry->var, '=') + 1, 1);
				}
			}
		}
		else
			ft_set_tool(*av, value, 1, ENVAR);
		av++;
	}
	return (0);
}
