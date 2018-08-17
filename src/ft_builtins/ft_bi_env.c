/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:27:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:20:03 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_env_usage(char c)
{
	ft_dprintf(2,
			"env: illegal option -- %c\n"
			"usage: env [-iv] [-P utilpath] [-S string] [-u name]\n"
			"           [name=value ...] [utility [argument ...]]\n", c);
	exit(1);
}

int			ft_env_op(int p)
{
	char **env;

	env = get_environ()->envar;
	while (env && *env)
		if (p == ENV_CLEAR)
			ft_memdel((void*)env++);
		else if (p == ENV_PRINT)
			ft_printf("%s\n", *env++);
	return (0);
}

static int	ft_env_flags(char ***av, t_op *options)
{
	char	*str;
	char	*tmp;

	str = **av;
	while (*++str)
		if (*str == 'i')
			options->i = 1;
		else if (*str == 'v')
			options->v++
				? ft_printf("#env verbosity now at %d\n", options->v) : 0;
		else if (*str == 'u' || *str == 'S' || *str == 'P')
		{
			tmp = (!*(str + 1)) ? *(++*av) : (str + 1);
			*str == 'u' ? ft_unset_tool(tmp, ENVAR) : 0;
			*str == 'u' && options->v ? ft_printf("#env unset:\t%s\n", tmp) : 0;
			*str == 'P' ? options->ap = tmp : 0;
			*str == 'S' ? options->exec = ft_strdup_arr(*av) : 0;
			*str == 'S' ? free(options->exec[0]) : 0;
			*str == 'S' ? options->exec[0] = ft_strdup(tmp) : 0;
			return (*str == 'S' ? 1 : 0);
		}
		else
			ft_env_usage(*str);
	return (0);
}

static void	ft_options_init(t_op *options)
{
	char	*tmp;

	ft_bzero(options, sizeof(t_op));
	tmp = ft_getenv("PATH");
	options->p = tmp ? ft_strdup(tmp) : NULL;
	options->ap = options->p;
}

int			ft_env(char **av)
{
	char	*tmp;
	int		st;
	t_op	options;

	if (!get_environ()->pid && (get_environ()->pid = fork()))
		return (get_environ()->pid == -1 ? 256 : 0);
	ft_options_init(&options);
	while (*av && **av == '-' && !ft_env_flags(&av, &options))
		av++;
	options.i ? ft_env_op(ENV_CLEAR) : 0;
	options.i && options.v ? ft_printf("#env clearing environ\n") : 0;
	while (*av && !options.exec && (tmp = ft_strchr(*av, '=')))
	{
		options.v ? ft_printf("#env setenv:\t%s\n", *av) : 0;
		*tmp = 0;
		ft_set_tool(*av++, ++tmp, 1, ENVAR);
	}
	!options.exec && *av ? options.exec = ft_strdup_arr(av) : 0;
	if (options.v && options.exec && (st = -1))
		ft_printf("#env executing: %s\n", options.exec[0]);
	while (options.v && options.exec && options.exec[(++st)])
		ft_printf("#env\targ[%d]= '%s'\n", st, options.exec[st]);
	st = !(options.exec && (++get_environ()->pid)) ? ft_env_op(ENV_PRINT)
		: ft_argv_exec(options.exec, options.ap, -1);
	exit(st);
}
