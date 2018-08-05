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
//
// static char	*search_hist_by_number(char *ptr, t_hist *hist)
// {
// 	unsigned num;
//
// 	if (*ptr == '-')
// 		num = hist->no - (unsigned)ft_atoi(ptr + 1);
// 	else
// 		num = (unsigned)ft_atoi(ptr);
// 	while (hist)
// 	{
// 		if (hist->no == num)
// 			return (hist->str);
// 		hist = hist->prv;
// 	}
// 	return (NULL);
// }
//
// static char	*srana_func(char *ptr)
// {
// 	t_hist	*hist;
//
// 	hist = gsh_r_history_bucket(-2, 0);
// 	if (*ptr == '!')
// 		return (hist->prv->str);
// 	else if (ft_isnumber(ptr) && *ptr != '+')
// 		return (search_hist_by_number(ptr, hist));
// 	else if (*ptr == '?')
// 		while (hist)
// 		{
// 			if (hist->str && ft_strstr(hist->str, ptr + 1))
// 				return (hist->str);
// 			hist = hist->prv;
// 		}
// 	else
// 		while (hist)
// 		{
// 			if (hist->str && !ft_strncmp(hist->str, ptr, ft_strlen(ptr)))
// 				return (hist->str);
// 			hist = hist->prv;
// 		}
// 	return (NULL);
// }
//
// static int	exclamation_replacer(char **ln, int *k, int z)
// {
// 	char	ptr[LINE_SIZE];
// 	char	*str;
//
// 	while ((*ln)[*k + z])
// 	{
// 		z++;
// 		if ((*ln)[*k + z] == ' ' || (*ln)[*k + z] == '\t' || (*ln)[*k + z] ==
// 	'\n' || (*ln)[*k + z] == '\n' || (*ln)[*k + z] == '\'' || (*ln)[*k + z] ==
// 	';' || (*ln)[*k + z] == '|' || (*ln)[*k + z] == '&')
// 			break ;
// 		else
// 			ptr[z - 1] = (*ln)[*k + z];
// 	}
// 	ptr[z - 1] = 0;
// 	if ((str = srana_func(ptr)))
// 	{
// 		*ln = ft_realloc(ft_strlen(*ln) - z + ft_strlen(str) + 1,
// 			ft_strlen(*ln) + 1, *ln);
// 		ft_memmove(*ln + *k + ft_strlen(str), *ln + *k + z,
// 			ft_strlen(*ln) - *k - z + 1);
// 		ft_memmove(*ln + *k, str, ft_strlen(str));
// 		*k += ft_strlen(str);
// 		return (1);
// 	}
// 	return (0);
// }

int		rl_mark_replacer(void)
{
	return (0);
}

char	*ft_rl_history_replace_mark(void)
{
	t_line	*tmp;
	char	mrk;
	char	sign;
	char	*s;

	mrk = 0;
	tmp = get_term()->cursor;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->ch == '!' && !mrk && !(tmp->prev && tmp->prev->ch == '\\')
			&& tmp->next && tmp->next->ch != '\t' && tmp->next->ch != '\n'
			&& tmp->next->ch != ' ')
		{
			if (!rl_mark_replacer())
			{
				write(1, "\a", 1);
				return (line_tostr(&get_term()->cursor, 2));
			}
			else
				sign = 1;
		}
		tmp->ch == '\\' ? mrk ^= 1 : 0;
		tmp = tmp->next;
	}
	s = NULL;
	s = line_tostr(&get_term()->cursor, 0);
	ft_putendl(s);
	return (s);
}
