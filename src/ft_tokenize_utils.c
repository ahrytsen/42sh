/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:11:31 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:24:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_token_del(void *token, size_t size)
{
	(void)size;
	if (((t_token*)token)->type >= heredoc
		&& ((t_token*)token)->type <= herestr)
		free(((t_token*)token)->data.redir.hd);
	free(token);
}

int		ft_isseparator(int c)
{
	return (ft_strchr("|&;<> \t\n", c) ? 1 : 0);
}

int		ft_check_redir(t_token *prev, t_token *next, char *ln)
{
	if (prev && prev->type > or && !prev->data.redir.right)
	{
		ft_dprintf(2, "21sh: unexpected token `%s'\n",
					ft_tname(next ? next->type : 0));
		return (1);
	}
	else if (next && next->type > or && !*ln)
	{
		ft_dprintf(2, "21sh: unexpected token `%s'\n",
					ft_tname(0));
		return (1);
	}
	return (0);
}

void	ft_skip_slash(char **s)
{
	if (*++(*s))
		(*s)++;
}

int		ft_skip_qoutes(char **s)
{
	char	q;

	q = *(*s)++;
	while (**s != q)
		if (!**s
			&& ft_dprintf(2, "21sh: %s `%c'\n",
						"unexpected EOF while looking for matching", q))
			return (1);
		else if (q == '"' && **s == '`')
			ft_skip_qoutes(s);
		else if (q != '\'' && **s == '\\' && (*s)++)
			**s ? (*s)++ : 0;
		else
			(*s)++;
	(*s)++;
	return (0);
}
