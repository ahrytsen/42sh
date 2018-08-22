/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:16:07 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/17 20:44:31 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			ft_isoperator(t_token *tok)
{
	return ((tok->type >= bg_op && tok->type <= or) ? 1 : 0);
}

static void	ft_get_operator(t_list **toks, t_ast *ast_node)
{
	t_list	*tmp;
	t_token	*tok;

	tmp = *toks;
	*toks = (*toks)->next;
	tmp->next = NULL;
	tok = tmp->content;
	if (tok->type == bg_op)
		ast_node->type = ast_bg;
	else if (tok->type == semi || tok->type == nl)
		ast_node->type = ast_semi;
	else if (tok->type == and)
		ast_node->type = ast_and;
	else if (tok->type == or)
		ast_node->type = ast_or;
	ft_lstdel(&tmp, ft_token_del);
}

static void	ft_get_cmd(t_list **toks, t_ast *ast_node)
{
	t_list	*tmp;

	ast_node->toks = *toks;
	ast_node->type = cmd;
	while (*toks && !ft_isoperator((*toks)->content))
	{
		tmp = *toks;
		*toks = (*toks)->next;
	}
	if (*toks && ((t_token*)(*toks)->content)->type == bg_op)
		ast_node->bg = 1;
	tmp->next = NULL;
}

int			ft_ast_get_token(t_list **toks, t_ast *ast_node, t_ast *prev)
{
	ft_bzero(ast_node, sizeof(t_ast));
	ft_isoperator((*toks)->content)
		? ft_get_operator(toks, ast_node) : ft_get_cmd(toks, ast_node);
	if ((ast_node->type > cmd && (!prev || prev->type > cmd))
		&& ft_dprintf(2, "42sh: syntax error near unexpected token `%s'\n",
					ft_ast_name(ast_node->type)))
		return (1);
	return (0);
}

t_ast		*ft_ast_make(t_list **toks)
{
	t_ast	*ast;
	t_ast	*tmp;
	t_ast	ast_node;

	ast = NULL;
	while (*toks)
		if (ft_ast_get_token(toks, &ast_node, ast)
			|| !(tmp = ft_ast_push(ast, &ast_node))
			|| !(ast = tmp))
		{
			ft_lstdel(&ast_node.toks, ft_token_del);
			return (ft_ast_del(ast, 1));
		}
	if (ast && ast->type != cmd && ast->type != ast_semi && ast->type != ast_bg
		&& write(2, "42sh: syntax error near unexpected EOF\n", 39))
		return (ft_ast_del(ast, 1));
	while (ast && ast->prev)
		ast = ast->prev;
	return (ast);
}
