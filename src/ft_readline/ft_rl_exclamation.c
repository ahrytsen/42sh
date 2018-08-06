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

static t_hist	*search_hist_by_number(char *ptr)
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
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

static t_line	*rl_match_history(char *ptr)
{
	t_hist	*hist;
	char *str;

	hist = get_term()->hist;
	if (*ptr == '!')
		return (hist->prev->line);
	if (ft_isnumber(ptr) && *ptr != '+')
		return (search_hist_by_number(ptr)->line);
	while (hist)
	{
		if (hist->line)
		{
			str = line_tostr(&hist->line, 0);
			if ((*ptr == '?' && ft_strstr(str, ptr + 1))
			|| !ft_strncmp(str, ptr, ft_strlen(ptr)))
			{
				free(str);
				return (hist->line);
			}
			free(str);
		}
		hist = hist->prev;
	}
	return (NULL);
}

static int		rl_mark_replacer(t_line **cur)
{
	t_line	*tmp;
	t_line	*rat;
	char	ptr[4096];
	int		k;

	tmp = (*cur);
	k = 0;
	while ((*cur)->next && (*cur = (*cur)->next))
	{
		if ((*cur)->ch == ' ' || (*cur)->ch == '\t' || (*cur)->ch == '\n'
		|| (*cur)->ch == '\'' || (*cur)->ch == ';' || (*cur)->ch == '|'
		|| (*cur)->ch == '&' || (*cur)->ch == '\"')
			break ;
		else
			ptr[k] = (*cur)->ch;
		k++;
	}
	ptr[k] = 0;
	if ((rat = rl_match_history(ptr)))
	{
		while (k-- + 1)
			ft_back_space();
		if (tmp->prev)
			tmp->prev->next = rat;
		ft_printf("[%c]\n", rat->prev->ch);
		// rat->prev = tmp->prev;
		while (rat->next)
			rat = rat->next;
		rat->next = *cur;
		(*cur)->prev = rat;
		return (1);
	}
	write(1, "\a", 1);
	return (0);
}

char			*ft_rl_history_replace_mark(t_line **cur)
{
	char	mrk;
	char	sign;
	char	*s;

	mrk = 0;
	while ((*cur)->prev)
		*cur = (*cur)->prev;
	while (*cur && (*cur)->next)
	{
		if ((*cur)->ch == '!' && !mrk && !((*cur)->prev
		&& (*cur)->prev->ch == '\\') && (*cur)->next->ch != '\t'
		&& (*cur)->next->ch != '\n' && (*cur)->next->ch != ' '
		&& (*cur)->next->ch != ';' && (*cur)->next->ch != '|'
		&& (*cur)->next->ch != '&')
		{
			if (!rl_mark_replacer(cur))
				return (line_tostr(cur, 0));
			sign = 1;
		}
		(*cur)->ch == '\'' ? mrk ^= 1 : 0;
		*cur = (*cur)->next;
	}
	write(1, "#", 1);
	*cur = (*cur)->prev;
	write(1, "@", 1);
	s = line_tostr(cur, 0);
	write(1, "$", 1);
	ft_putendl(s);
	return (s);
}
