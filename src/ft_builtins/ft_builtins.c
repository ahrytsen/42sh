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

int			ft_echo(char **av)
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

int			ft_exit(char **av)
{
	char	*tmp;

	if (get_environ()->is_interactive)
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

static int	ft_exec_exec(char **cmd, int bg)
{
	char	*bin_path;
	int		st;

	if (!cmd || !*cmd)
		return (0);
	bin_path = NULL;
	if (ft_strchr(*cmd, '/'))
		st = ft_exec_bypath(cmd, *cmd, bg);
	else
	{
		if ((bin_path = ft_search_bin(*cmd, NULL)))
			st = ft_exec_bypath(cmd, bin_path, bg);
		else if ((st = 127))
			ft_dprintf(2, "%s: command not found\n", *cmd);
	}
	free(bin_path);
	return (st);
}

int			ft_exec(char **av)
{
	pid_t	tmp;
	int		rat;
	int		shlvl;
	char	*ptr;

	tmp = get_environ()->pid;
	if (!av || !*av)
		return (0);
	get_environ()->pid = 1;
	ptr = ft_getenv("SHLVL");
	shlvl = ft_atoi(ptr);
	ptr = ft_itoa(shlvl - 1);
	ft_set_tool("SHLVL", ptr, 1, ENVAR);
	free(ptr);
	if (!(rat = ft_exec_exec(av, -1)))
		exit(0);
	ptr = ft_getenv("SHLVL");
	shlvl = ft_atoi(ptr);
	ptr = ft_itoa(shlvl + 1);
	ft_set_tool("SHLVL", ptr, 1, ENVAR);
	free(ptr);
	get_environ()->pid = tmp;
	return (rat);
}
