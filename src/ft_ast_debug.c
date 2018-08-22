/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 21:05:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/17 20:47:09 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const char	*ft_ast_name(enum e_ast_type type)
{
	static const char *const	names[] = {
		"cmd", "&&", "||", "&", ";", ";;"
	};

	if (type >= cmd && type <= ast_dsemi)
		return (names[type]);
	else
		return ("unknown token");
}

static void	test(t_list *elem)
{
	t_token	*tok;

	tok = elem->content;
	if (tok->type != redir && ft_printf("[%s]", ft_tname(tok)))
		return ;
	ft_printf("[%d %s %s]", tok->data.redir.left,
				ft_tname(tok), tok->data.redir.right);
}

static void	test_ast(t_ast *ast)
{
	t_cmd	*tmp;

	if (!ast)
		return ;
	test_ast(ast->right);
	if (ast->type == cmd)
	{
		tmp = ast->cmd;
		while (tmp)
		{
			ft_lstiter(tmp->toks, test);
			tmp = tmp->next;
			tmp ? ft_printf("[|]") : 0;
		}
	}
	else
		ft_printf("[%s]", ft_ast_name(ast->type));
	test_ast(ast->left);
}

void		ft_print_ast(t_ast *ast)
{
	if (ft_getenv("TEST_AST"))
	{
		test_ast(ast);
		ast ? write(1, "\n", 1) : 0;
	}
}

void		ft_print_toks(t_list *toks)
{
	if (ft_getenv("TEST_TOKS"))
	{
		ft_lstiter(toks, test);
		toks ? write(1, "\n", 1) : 0;
	}
}
