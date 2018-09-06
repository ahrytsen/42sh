/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_check_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:22:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/06 15:10:17 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static int	skip_slash(char **ln)
{
	(*ln)++;
	if (**ln)
		(*ln)++;
	else
	{
		get_term()->prompt = P_BSLASH;
		return (1);
	}
	return (0);
}

static int	skip_qoutes(char **ln)
{
	char	q;

	q = *(*ln)++;
	while (**ln != q)
		if (!**ln && (get_term()->prompt = q))
			return (1);
		else if (q == '"' && **ln == '`')
		{
			if (skip_qoutes(ln))
				return (1);
		}
		else if (q == '"' && **ln == '$' && *(*ln + 1) == '(')
		{
			if (ft_rl_skip_subsh(ln))
				return (1);
		}
		else if (q != '\'' && **ln == '\\')
		{
			if (skip_slash(ln))
				return (1);
		}
		else
			(*ln)++;
	(*ln)++;
	return (0);
}

int			ft_rl_skip_subsh(char **ln)
{
	int tmp;

	tmp = (**ln == '$' ? P_CMDSUBST : P_SUBSH);
	*ln += (**ln == '$' ? 2 : 1);
	while (**ln != ')')
		if (!**ln && (get_term()->prompt = tmp))
			return (1);
		else if (**ln == '\'' || **ln == '`' || **ln == '"')
		{
			if (skip_qoutes(ln))
				return (1);
		}
		else if ((**ln == '$' && *(*ln + 1) == '(') || **ln == '(')
		{
			if (ft_rl_skip_subsh(ln))
				return (1);
		}
		else if (**ln == '\\')
			*++(*ln) ? (*ln)++ : 0;
		else
			(*ln)++;
	(*ln)++;
	return (0);
}

static void	ft_remove_comment(char *ln)
{
	int		tmp_p;
	char	prev;

	tmp_p = get_term()->prompt;
	prev = '\0';
	while (*ln)
		if (ft_strchr("\"'`", *ln))
			skip_qoutes(&ln);
		else if (*ln == '(' || (*ln == '$' && ln[1] == '('))
			ft_rl_skip_subsh(&ln);
		else if (*ln == '\\')
			skip_slash(&ln);
		else if (*ln == '#' && (!prev || ft_isseparator(prev)))
		{
			*ln = '\0';
			break ;
		}
		else
			prev = *ln++;
	get_term()->prompt = tmp_p;
}

int			ft_check_line(char *ln)
{
	if (get_term()->prompt == P_HEREDOC)
		return (ln ? 0 : 1);
	if (!ln && !(get_term()->prompt = P_USER))
		return (1);
	ft_remove_comment(ln);
	while (*ln)
		if (*ln == '"' || *ln == '\'' || *ln == '`')
		{
			if (skip_qoutes(&ln))
				return (1);
		}
		else if (*ln == '(' || (*ln == '$' && *(ln + 1) == '('))
		{
			if (ft_rl_skip_subsh(&ln))
				return (1);
		}
		else if (*ln == '\\')
		{
			if (skip_slash(&ln))
				return (1);
		}
		else
			ln++;
	get_term()->prompt = P_USER;
	return (0);
}
