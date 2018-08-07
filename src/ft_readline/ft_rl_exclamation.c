/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_exclamation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 16:02:46 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/05 16:03:01 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	*search_hist_by_number(char *ptr)
{
	unsigned	num;
	t_hist		*tmp;

	tmp = get_term()->hist;
	if (*ptr == '-')
		num = tmp->no - (unsigned)ft_atoi(ptr + 1);
	else
		num = (unsigned)ft_atoi(ptr);
	while (tmp)
	{
		if (tmp->no == num)
			return (line_tostr(&tmp->line, 0));
		tmp = tmp->prev;
	}
	return (NULL);
}

static char	*rl_match_history(char *ptr)
{
	t_hist	*hist;
	char	*str;

	hist = get_term()->hist;
	if (*ptr == '!' && hist->prev)
		return (line_tostr(&hist->prev->line, 0));
	else if (*ptr && ft_isnumber(ptr) && *ptr != '+')
		return (search_hist_by_number(ptr));
	else if (*ptr)
		while (hist)
		{
			if (hist->line)
			{
				str = line_tostr(&hist->line, 0);
				if ((*ptr == '?' && ft_strstr(str, ptr + 1))
				|| !ft_strncmp(str, ptr, ft_strlen(ptr)))
					return (str);
				free(str);
			}
			hist = hist->prev;
		}
	return (NULL);
}

static int	rl_mark_replacer(t_line **cur)									//28
{
	char	*tmp;
	char	*rat;
	char	ptr[4096];
	int		k;

	k = 0;
	while ((*cur)->next && (*cur = (*cur)->next))
	{
		if ((*cur)->ch == ' ' || (*cur)->ch == '\t' || (*cur)->ch == '\n'
		|| (*cur)->ch == '\'' || (*cur)->ch == ';' || (*cur)->ch == '|'
		|| (*cur)->ch == '&' || (*cur)->ch == '\"' || (*cur)->ch == '\0'
		|| (k && (*cur)->prev->ch == '!'))
			break ;
		ptr[k++] = (*cur)->ch;
	}
	ptr[k] = 0;
	if ((rat = rl_match_history(ptr)))
	{
		while (k-- + 1)
			ft_back_space();
		tmp = rat;
		while (*rat)
			line_add(*cur, (uint64_t)(*rat++));
		free(tmp);
		return (1);
	}
	ft_dprintf(2, "42sh: event not found: %s\n", ptr);
	return (0);
}

char		*ft_rl_history_replace_mark(t_line **cur)
{
	char	mk[3];
	char	*s;

	mk[1] = 0;
	mk[2] = 0;
	s = NULL;
	while ((*cur)->prev)
		*cur = (*cur)->prev;
	while (*cur && (*cur)->next)
	{
		if ((*cur)->ch == '!' && !mk[1] && !((*cur)->prev && (*cur)->prev->ch
		== '\\') && (*mk = (char)(*cur)->next->ch) != '\t' && *mk != '\n'
		&& *mk != ' ' && *mk != ';' && *mk != '|' && *mk != '&' && *mk != '\0')
		{
			if (!rl_mark_replacer(cur))
				return (NULL);
			mk[2] = 1;
		}
		(*cur)->ch == '\'' ? mk[1] ^= 1 : 0;
		(*cur)->next ? *cur = (*cur)->next : 0;
	}
	if (mk[2] && (s = line_tostr(cur, 0)))
		ft_printf("%s\n", s);
	return (s);
}
