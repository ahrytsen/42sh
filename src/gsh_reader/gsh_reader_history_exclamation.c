/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_history_exclamation.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:19:51 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/14 13:19:52 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static char	*search_hist_by_number(char *ptr, t_hist *hist)
{
	unsigned num;

	if (*ptr == '-')
		num = hist->no - (unsigned)ft_atoi(ptr + 1);
	else
		num = (unsigned)ft_atoi(ptr);
	while (hist)
	{
		if (hist->no == num)
			return (hist->str);
		hist = hist->prv;
	}
	return (NULL);
}

static char	*srana_func(char *ptr)
{
	t_hist	*hist;

	hist = gsh_r_history_bucket(-2, 0);
	if (*ptr == '!')
		return (hist->prv->str);
	else if (ft_isnumber(ptr) && *ptr != '+')
		return (search_hist_by_number(ptr, hist));
	else if (*ptr == '?')
		while (hist)
		{
			if (hist->str && ft_strstr(hist->str, ptr + 1))
				return (hist->str);
			hist = hist->prv;
		}
	else
		while (hist)
		{
			if (hist->str && !ft_strncmp(hist->str, ptr, ft_strlen(ptr)))
				return (hist->str);
			hist = hist->prv;
		}
	return (NULL);
}

static int	exclamation_replacer(char **ln, int *k, int z)
{
	char	ptr[LINE_SIZE];
	char	*str;

	while ((*ln)[*k + z])
	{
		z++;
		if ((*ln)[*k + z] == ' ' || (*ln)[*k + z] == '\t' || (*ln)[*k + z] ==
	'\n' || (*ln)[*k + z] == '\n' || (*ln)[*k + z] == '\'' || (*ln)[*k + z] ==
	';' || (*ln)[*k + z] == '|' || (*ln)[*k + z] == '&')
			break ;
		else
			ptr[z - 1] = (*ln)[*k + z];
	}
	ptr[z - 1] = 0;
	if ((str = srana_func(ptr)))
	{
		*ln = ft_realloc(ft_strlen(*ln) - z + ft_strlen(str) + 1,
			ft_strlen(*ln) + 1, *ln);
		ft_memmove(*ln + *k + ft_strlen(str), *ln + *k + z,
			ft_strlen(*ln) - *k - z + 1);
		ft_memmove(*ln + *k, str, ft_strlen(str));
		*k += ft_strlen(str);
		return (1);
	}
	return (0);
}

char		*gsh_r_history_replace_mark(char *ln, int k)
{
	int		c;
	int		m;

	c = 0;
	m = 0;
	while (ln[k])
	{
		if (ln[k] == '!' && !(c || (k && ln[k - 1] == '\\')) && ln[k + 1]
			&& ln[k + 1] != '\t' && ln[k + 1] != '\n' && ln[k + 1] != ' ')
		{
			if (!exclamation_replacer(&ln, &k, 0))
			{
				free(ln);
				ln = NULL;
				break ;
			}
			else
				m = 1;
		}
		(ln[k] == '\'') ? c ^= 1 : 0;
		k++;
	}
	ln ? ln[k] = 0 : 0;
	m ? ft_putendl(ln) : 0;
	return (ln);
}
