/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 12:58:35 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/26 12:58:37 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void		gsh_r_check_size(t_hist *hist)
{
	unsigned	num;
	t_hist		*tmp;

	if (hist->no <= g_hst_sz)
		return ;
	num = hist->no - g_hst_sz;
	while (hist->prv)
		hist = hist->prv;
	while (hist && hist->no <= num)
	{
		tmp = hist;
		hist = hist->nxt;
		hist->prv = NULL;
		free(tmp->tmp);
		free(tmp->str);
		free(tmp);
	}
}

static t_hist	*gsh_r_hist_add_elem(t_hist *hist)
{
	if (!hist)
	{
		hist = (t_hist *)malloc(sizeof(t_hist));
		hist->tmp = ft_strdup("");
		hist->str = NULL;
		hist->prv = NULL;
		hist->nxt = NULL;
		hist->no = 1;
	}
	else if (hist->str)
	{
		hist->nxt = (t_hist *)malloc(sizeof(t_hist));
		hist->nxt->tmp = ft_strdup("");
		hist->nxt->str = NULL;
		hist->nxt->prv = hist;
		hist->nxt->nxt = NULL;
		hist->nxt->no = hist->no + 1;
		hist = hist->nxt;
	}
	gsh_r_check_size(hist);
	return (hist);
}

static t_hist	*gsh_r_hist_rewrite_elem(char *str, t_hist *hist)
{
	if (!hist)
		return (NULL);
	while (hist->prv)
		hist = hist->prv;
	while (hist->nxt)
	{
		free(hist->tmp);
		hist->tmp = NULL;
		hist = hist->nxt;
	}
	if (hist->tmp)
	{
		free(hist->tmp);
		hist->tmp = NULL;
	}
	if (str && !ft_is_blank(str))
		hist->str = ft_strdup(str);
	return (hist);
}

t_hist			*gsh_r_history_bucket(int mod, char *str)
{
	static t_hist	*hist;

	if ((mod == PGUP && !hist->prv) || (mod == PGDWN && !hist->nxt))
		write(0, "\a", 1);
	else if (mod == CREATE && g_hst_sz)
		hist = gsh_r_hist_add_elem(hist);
	else if (mod == ADD && g_hst_sz)
		hist = gsh_r_hist_rewrite_elem(str, hist);
	else if (mod == PGUP || mod == PGDWN)
		return (gsh_r_browse_history(mod, &hist, str));
	else if (mod == ERASE)
		hist = gsh_r_remove_history(hist);
	else if (mod == RETURN)
		return (hist);
	else if (mod == DELONE)
		hist = gsh_r_erase_elem(hist, (unsigned)ft_atoi(str));
	return (NULL);
}
