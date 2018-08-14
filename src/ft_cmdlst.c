/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:53:42 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/14 21:48:28 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_get_pipe(t_list **toks, t_cmd *cmdlst)
{
	t_list	*tmp;

	tmp = *toks;
	*toks = (*toks)->next;
	tmp->next = NULL;
	ft_lstdel(&tmp, ft_token_del);
	if (!cmdlst || !*toks || ((t_token*)(*toks)->content)->type == pipeline)
	{
		write(2, "42sh: unexpected token `|'\n", 27);
		return (1);
	}
	return (0);
}

static int	ft_get_cmd(t_list **toks, t_cmd *cmd)
{
	t_list	*tmp;

	cmd->toks = *toks;
	tmp = *toks;
	while (*toks && ((t_token*)(*toks)->content)->type != pipeline
			&& ((t_token*)(*toks)->content)->type != subsh_on)
	{
		tmp = *toks;
		*toks = (*toks)->next;
	}
	tmp->next = NULL;
	if (*toks && ((t_token*)(*toks)->content)->type == subsh_)
	{
		ft_lstdel(&cmd->toks, ft_token_del);
		write(2, "42sh: unexpected token `('\n", 27);
		return (1);
	}
	return (0);
}

static int	ft_get_sub_sh(t_list **toks, t_cmd *cmd)
{
	cmd->toks = *toks;
	cmd->subsh = ((t_token*)cmd->toks->content)->data.word;
	*toks = (*toks)->next;
	cmd->toks->next = NULL;
	if (*toks && ((t_token*)(*toks)->content)->type != pipeline)
	{
		ft_lstdel(&cmd->toks, ft_token_del);
		((t_token*)(*toks)->content)->type == word
			? ft_dprintf(2, "42sh: unexpected token `%s'\n",
						((t_token*)(*toks)->content)->data.word)
			: write(2, "42sh: unexpected token `('\n", 27);
		return (1);
	}
	return (0);
}

t_cmd		*ft_cmdlst_make(t_list **toks)
{
	t_cmd	*cmdlst;
	t_cmd	*tmp;
	t_cmd	cmd;

	cmdlst = NULL;
	while (*toks)
	{
		ft_bzero(&cmd, sizeof(cmd));
		if ((*toks && ((t_token*)(*toks)->content)->type == pipeline
				&& ft_get_pipe(toks, cmdlst))
			|| (*toks && ((t_token*)(*toks)->content)->type == subsh_on
				&& ft_get_sub_sh(toks, &cmd))
			|| (*toks && ((t_token*)(*toks)->content)->type != pipeline
				&& ((t_token*)(*toks)->content)->type != subsh
				&& ft_get_cmd(toks, &cmd))
			|| !(tmp = ft_cmdlst_push(cmdlst ? tmp : cmdlst, &cmd)))
			return (ft_cmdlst_del(cmdlst));
		!cmdlst ? cmdlst = tmp : 0;
	}
	return (cmdlst);
}
