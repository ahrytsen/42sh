/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 19:53:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/17 19:15:17 by ahrytsen         ###   ########.fr       */
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
			system("leaks --quiet 42sh");
			return (!i ? get_environ()->st : 1);
		}
		if (cmds && (toks = ft_tokenize(cmds)) && ft_heredoc(toks))
		{
			ft_print_toks(toks);
			ast = ft_ast_make(&toks);
			ft_print_ast(ast);
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
	ft_init();
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
