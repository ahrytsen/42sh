/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:55:11 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:22:38 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_ast_and_exec(t_ast *ast)
{
	int	ret_right;

	if (!(ret_right = ft_ast_exec(ast->right)))
		return (ft_ast_exec(ast->left));
	else
		return (ret_right);
}

static int	ft_ast_or_exec(t_ast *ast)
{
	int	ret_right;

	if (!(ret_right = ft_ast_exec(ast->right)))
		return (ret_right);
	else
		return (ft_ast_exec(ast->left));
}

static int	ft_ast_cmd_exec(t_ast *ast)
{
	int	ret;

	ret = ft_cmdlst_exec(ast->cmd, ast->bg);
	ast->cmd = NULL;
	return (ft_status_job(ret));
}

static int	ft_ast_smcln_exec(t_ast *ast)
{
	int	ret_right;

	ret_right = ft_ast_exec(ast->right);
	return (ast->left ? ft_ast_exec(ast->left) : ret_right);
}

int			ft_ast_exec(t_ast *ast)
{
	if (!ast)
		return (0);
	else if (ast->type == cmd)
		return (ft_ast_cmd_exec(ast));
	else if (ast->type == ast_and)
		return (ft_ast_and_exec(ast));
	else if (ast->type == ast_or)
		return (ft_ast_or_exec(ast));
	else if (ast->type == ast_bg || ast->type == ast_smcln)
		return (ft_ast_smcln_exec(ast));
	else
		return (-1);
}
