/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 20:36:35 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/02 20:51:59 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	ft_cmd_print_smpl(t_cmd *cmd)
{
	t_list	*toks;
	t_token	*tok;

	toks = cmd->toks;
	while (toks)
	{
		tok = toks->content;
		if (tok->type == redir)
			ft_printf(toks->next ? "%d%s %s " : "%d%s %s",
					tok->data.redir.left, ft_tname(tok), tok->data.redir.right);
		else
			ft_printf(toks->next ? "%s " : "%s", ft_tname(tok));
		toks = toks->next;
	}
}

static void	ft_ast_print(t_ast *ast)
{
	if (!ast)
		return ;
	ft_ast_print(ast->right);
	if (ast->type == cmd)
		ft_cmdlst_print(ast->cmd);
	else
		ft_printf(ast->left ? " %s " : " %s", ft_ast_name(ast->type));
	ft_ast_print(ast->left);
}

static void	ft_cmd_print_subsh(t_cmd *cmd)
{
	ft_printf("(");
	ft_ast_print(((t_token*)(cmd->toks->content))->data.sub_ast);
	ft_printf(")");
}

/*
**static void	ft_cmd_print_not(t_cmd *cmd)
**{
**	(void)cmd;
**}
**
**static void	ft_cmd_print_grp(t_cmd *cmd)
**{
**	(void)cmd;
**}
**
**static void	ft_cmd_print_case(t_cmd *cmd)
**{
**	(void)cmd;
**}
**
**static void	ft_cmd_print_for(t_cmd *cmd)
**{
**	(void)cmd;
**}
**
**static void	ft_cmd_print_if(t_cmd *cmd)
**{
**	(void)cmd;
**}
**
**static void	ft_cmd_print_until(t_cmd *cmd)
**{
**	(void)cmd;
**}
**
**static void	ft_cmd_print_while(t_cmd *cmd)
**{
**	(void)cmd;
**}
**		, ft_cmd_print_not,
**		ft_cmd_print_grp, ft_cmd_print_case, ft_cmd_print_for,
**		ft_cmd_print_if, ft_cmd_print_until, ft_cmd_print_while
**	};
*/

void		ft_cmd_print(t_cmd *cmd)
{
	static void	(*const print[])(t_cmd*) = {
		ft_cmd_print_smpl, ft_cmd_print_subsh
	};

	if (cmd->type >= cmd_smpl && cmd->type <= cmd_subsh)
		print[cmd->type] ? print[cmd->type](cmd) : 0;
}
