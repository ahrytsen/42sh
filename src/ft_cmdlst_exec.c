/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:41:55 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/15 21:13:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_pl_make(int pl[2], t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(pl) && write(2, "42sh: pipe error\n", 17))
			return (1);
		cmd->p_out = pl[1];
		cmd->next->p_in = pl[0];
	}
	return (0);
}

static int	ft_subsh_exec(t_cmd *cmd)
{
	t_list	*toks;
	t_ast	*ast;

	ast = NULL;
	toks = NULL;
	get_environ()->st = 1;
	if (cmd->subsh && (toks = ft_tokenize(cmd->subsh ? NULL:NULL))
		&& ft_heredoc(toks))
	{
		ast = ft_ast_make(&toks);
		get_environ()->st = ft_ast_exec(ast);
		ast = ft_ast_del(ast, 1);
		ft_lstdel(&toks, ft_token_del);
	}
	exit(get_environ()->st);
}

static int	ft_cmd_exec_chld(t_cmd *cmd, int bg)
{
	if (cmd->next || cmd->prev || bg)
	{
		cmd->prev ? dup2(cmd->p_in, 0) : 0;
		cmd->prev ? close(cmd->p_in) : 0;
		cmd->next ? dup2(cmd->p_out, 1) : 0;
		cmd->next ? close(cmd->p_out) : 0;
		ft_set_sh_signal(bg ? S_CHLD : S_CHLD_FG);
		bg = -1;
	}
	if (ft_redirection(cmd->toks))
		cmd->ret = 1;
	else
		cmd->ret = cmd->subsh ? ft_subsh_exec(cmd)
			: ft_argv_exec(cmd->av, NULL, bg);
	cmd->pid = get_environ()->pid;
	get_environ()->pgid = cmd->pid;
	ft_redirection_close(cmd->toks);
	if (cmd->next || cmd->prev || bg)
		exit(cmd->ret);
	return (cmd->ret);
}

static int	ft_cmd_exec(t_cmd *cmd, int bg)
{
	static int	pl[2];

	if (ft_pl_make(pl, cmd)
		|| (!cmd->subsh && !(cmd->av = ft_argv_make(cmd->toks))
			&& write(2, "42sh: malloc error\n", 19)))
		return (1);
	if ((cmd->next || cmd->prev || bg || cmd->subsh) && (cmd->pid = fork()))
	{
		if (cmd->pid == -1 && write(2, "42sh: fork() error\n", 19))
			return (1);
		get_environ()->pid = cmd->pid;
		if (get_environ()->is_interactive)
		{
			!get_environ()->pgid ? get_environ()->pgid = cmd->pid : 0;
			setpgid(get_environ()->pid, get_environ()->pgid);
		}
		return (0);
	}
	else
		return (ft_cmd_exec_chld(cmd, bg));
}

int			ft_cmdlst_exec(t_cmd *cmd, int bg)
{
	int	ret;
	int	ret2;

	while (1)
	{
		cmd->ret = ft_cmd_exec(cmd, bg);
		cmd->next ? close(cmd->p_out) : 0;
		cmd->prev ? close(cmd->p_in) : 0;
		if (cmd->ret || !cmd->next)
			break ;
		cmd = cmd->next;
	}
	(cmd->next || cmd->prev || bg) ? 0 : ft_fildes(FD_RESTORE);
	ret = cmd->ret;
	ret2 = ft_control_job(cmd, bg, 0);
	if (ret || (!WIFSTOPPED(ret2) && !bg))
		ft_cmdlst_del(cmd);
	return (ret2);
}
