/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 21:05:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/15 21:05:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	test(t_list *elem)
{
	t_token	*tok;

	tok = elem->content;
	if ((tok->type == word && ft_printf("[%s]", tok->data.word))
		|| (tok->type == subsh_on && ft_printf("[(]"))
		|| (tok->type == subsh_off && ft_printf("[)]")))
		return ;
	ft_printf("[%d", tok->data.redir.left);
	if (tok->type == heredoc || tok->type == heredoc_t)
		tok->type == heredoc ? ft_printf(" <-*heredoc*-> ")
			: ft_printf(" <-*heredoc_t*-> ");
	else if (tok->type == herestr || tok->type == open_file)
		tok->type == herestr ? ft_printf(" <-*herestr*-> ")
			: ft_printf(" <-*open_file*-> ");
	else if (tok->type == read_in || tok->type == read_in_and)
		tok->type == read_in ? ft_printf(" <-*read_in*-> ")
			: ft_printf(" <-*read_in_and*-> ");
	else if (tok->type == read_out || tok->type == read_out_and)
		tok->type == read_out ? ft_printf(" <-*read_out*-> ")
			: ft_printf(" <-*read_out_and*-> ");
	else if (tok->type == read_out_pipe || tok->type == and_read_out)
		tok->type == read_out_pipe ? ft_printf(" <-*read_out_pipe*-> ")
			: ft_printf(" <-*and_read_out*-> ");
	else if (tok->type == read_out_apend)
		ft_printf(" <-*read_out_apend*-> ");
	ft_printf("%s]", tok->data.redir.right);
}

static void	test_ast(t_ast *ast)
{
	t_cmd	*tmp;

	if (!ast)
		return ;
	test_ast(ast->right);
	if (ast->type == ast_and)
		ft_printf("[&&]");
	else if (ast->type == ast_or)
		ft_printf("[||]");
	else if (ast->type == ast_bg)
		ft_printf("[&]");
	else if (ast->type == ast_smcln)
		ft_printf("[;]");
	else
	{
		tmp = ast->cmd;
		while (tmp)
		{
			ft_lstiter(tmp->toks, test);
			tmp = tmp->next;
			tmp ? ft_printf("[|]") : 0;
		}
	}
	test_ast(ast->left);
}

static void	ft_print_ast(t_ast *ast)
{
	if (ft_getenv("TEST_AST"))
	{
		test_ast(ast);
		ast ? write(1, "\n", 1) : 0;
	}
}
