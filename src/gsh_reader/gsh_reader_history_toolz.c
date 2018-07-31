/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_history_toolz.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:37:20 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/11 13:37:21 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static t_hist	*mega_uber_trivial_name_fo_function(t_hist *hist, t_hist *prev,
	unsigned num)
{
	t_hist *next;

	next = hist->nxt;
	free(hist->str);
	free(hist->tmp);
	free(hist);
	if (prev)
		prev->nxt = next;
	if (next)
		next->prv = prev;
	while (next)
	{
		prev = next;
		next->no = num;
		next = next->nxt;
		num++;
	}
	return (prev);
}

t_hist			*gsh_r_erase_elem(t_hist *hist, unsigned num)
{
	t_hist *prev;

	prev = NULL;
	if (!hist)
		return (NULL);
	while (hist->prv)
		hist = hist->prv;
	while (hist)
	{
		if (hist->no == num)
			return (mega_uber_trivial_name_fo_function(hist, prev, num));
		prev = hist;
		hist = hist->nxt;
	}
	return (prev);
}

t_hist			*gsh_r_remove_history(t_hist *hist)
{
	t_hist *tmp;

	if (!hist)
		return (NULL);
	while (hist->prv)
		hist = hist->prv;
	while (hist)
	{
		tmp = hist;
		hist = hist->nxt;
		if (tmp->str)
			free(tmp->str);
		if (tmp->tmp)
			free(tmp->tmp);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

t_hist			*gsh_r_browse_history(int mod, t_hist **hist, char *str)
{
	if (mod == PGUP)
	{
		if ((*hist)->tmp)
			free((*hist)->tmp);
		(*hist)->tmp = ft_strdup(str);
		(*hist) = (*hist)->prv;
	}
	else if (mod == PGDWN)
	{
		if ((*hist)->tmp)
			free((*hist)->tmp);
		(*hist)->tmp = ft_strdup(str);
		(*hist) = (*hist)->nxt;
	}
	return (*hist);
}
