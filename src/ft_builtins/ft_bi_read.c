/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 08:17:22 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/04 02:47:58 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	handler_func(int i)
{
	(void)i;
}

static void	handle_sigint(void)
{
	struct sigaction	int_handler;

	ft_bzero(&int_handler, sizeof(struct sigaction));
	int_handler.sa_handler = handler_func;
	sigaction(SIGINT, &int_handler, 0);
}

static char	**check_flags(char **av, char *r_flag)
{
	char	*s;

	if (av)
		while (*av && **av == '-')
		{
			if (ft_strequ(*av, "--"))
				return (av + 1);
			s = *av;
			while (*++s)
				if (*s != 'r')
				{
					ft_dprintf(2, "42sh: read: %s: invalid option\n"
								"read: usage: read [-r] [name ...]\n", *av);
					return (NULL);
				}
				else
					*r_flag = 1;
			++av;
		}
	return (av);
}

static int	check_var_names(char **av)
{
	char	*s;

	if (av)
		while (*av)
		{
			s = *av;
			while (*s)
			{
				if (!ft_isword(*s))
				{
					ft_dprintf(2,
						"42sh: read: %s: not a valid identifier\n", *av);
					return (0);
				}
				++s;
			}
			++av;
		}
	return (1);
}

int			ft_bi_read(char **av)
{
	char	r_flag;

	r_flag = 0;
	if (get_environ()->is_interactive)
		handle_sigint();
	if (!(av = check_flags(av, &r_flag)) || !check_var_names(av))
		return (256);
	read_line(av, r_flag);
	if (get_environ()->is_interactive)
		signal(SIGINT, SIG_IGN);
	return (0);
}
