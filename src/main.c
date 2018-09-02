/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:53:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/31 05:39:34 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"

int			main_loop(int fd)
{
	char	*cmds;
	t_list	*toks;
	t_ast	*ast;
	int		i;

	ft_init_fd(fd);
	while (1)
	{
		toks = NULL;
		cmds = NULL;
		ast = NULL;
		if (!(i = ft_readline(fd, &cmds)) || (i == -1 && !ft_is_interrupted()))
		{
//			system("/usr/bin/leaks -quiet 42sh >>/Users/motofun/projects/42sh/leaks.txt 2>/dev/null");
			return (!i ? get_environ()->st : 1);
		}
		if (cmds && (toks = ft_tokenize(cmds)) && ft_heredoc(toks))
		{
			ast = ft_ast_make(&toks);
			get_environ()->st = ft_ast_exec(ast);
			ast = ft_ast_del(ast, 1);
		}
		ft_lstdel(&toks, ft_token_del);
		free(cmds);
	}
}

int			main(int ac, char **av)
{
	int i;
	int	fd;
	int	ret;

	i = 1;
	ft_init(ac, av);
	if (ac < 2)
		return (main_loop(STDIN_FILENO));
	while (i < ac)
	{
		if ((access(av[i], F_OK)
				&& ft_dprintf(2, "%s: no such file: %s\n", av[0], av[i]))
			|| (access(av[i], R_OK)
				&& ft_dprintf(2, "%s: permission denied: %s\n", av[0], av[i]))
			|| ((fd = open(av[i], O_RDONLY)) < 0
				&& ft_dprintf(2, "%s: open error: %s\n", av[0], av[i])))
			return (127);
		i++;
		ret = main_loop(fd);
	}
	return (ret);
}
