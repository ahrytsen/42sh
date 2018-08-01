/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:54:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/14 20:43:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static int		ft_getprior(t_ast_type type)
{
	if (type == cmd)
		return (1);
	else
		return (type == ast_and || type == ast_or ? 2 : 3);
}

static t_ast	*ft_add_up(t_ast *ast, t_ast *node)
{
	t_ast	*tmp;

	while (ast->prev && ft_getprior(ast->prev->type) < ft_getprior(node->type))
		ast = ast->prev;
	tmp = ast->prev;
	tmp ? tmp->left = node : 0;
	node->prev = tmp;
	node->right = ast;
	return (node);
}

static t_ast	*ft_add_left(t_ast *ast, t_ast *node)
{
	t_ast	*tmp;

	tmp = ast->left;
	ast->left = node;
	node->prev = ast;
	node->right = tmp;
	tmp ? tmp->prev = node : 0;
	return (node);
}

t_ast			*ft_ast_del(t_ast *ast, int up)
{
	if (!ast)
		return (NULL);
	while (up && ast->prev)
		ast = ast->prev;
	ast->right = ft_ast_del(ast->right, 0);
	ast->left = ft_ast_del(ast->left, 0);
	ft_lstdel(&ast->toks, ft_token_del);
	ast->cmd = ft_cmdlst_del(ast->cmd);
	free(ast);
	return (NULL);
}

t_ast			*ft_ast_push(t_ast *ast, t_ast *node)
{
	t_ast *new_node;

	if ((node->type == cmd
			&& !(node->cmd = ft_cmdlst_make(&node->toks)))
		|| (!(new_node = (t_ast*)malloc(sizeof(t_ast)))
			&& ft_dprintf(2, "21sh: malloc error\n")))
		return ((t_ast*)ft_cmdlst_del(node->cmd));
	node->toks = NULL;
	ft_memcpy(new_node, node, sizeof(t_ast));
	if (!ast)
		return (new_node);
	return ((ft_getprior(ast->type) > ft_getprior(new_node->type)
			? ft_add_left : ft_add_up)(ast, new_node));
}
