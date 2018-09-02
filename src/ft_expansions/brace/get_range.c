/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_range.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:31:24 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/01 20:18:17 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static t_list	*get_num_range(char **s)
{
	int		lim1;
	int		lim2;
	char	*tmp;
	t_list	*lst;

	lst = NULL;
	lim1 = ft_atoi(++(*s));
	*s += (**s == '+' || **s == '-' ? 1 : 0) + ft_count_digits(lim1) + 2;
	lim2 = ft_atoi(*s);
	*s += (**s == '+' || **s == '-' ? 1 : 0) + ft_count_digits(lim2) + 1;
	if (lim1 < lim2)
		while (lim1 <= lim2)
		{
			tmp = ft_itoa(lim1++);
			ft_lstpush_back(&lst, tmp, ft_strlen(tmp) + 1);
			free(tmp);
		}
	else
		while (lim1 >= lim2)
		{
			tmp = ft_itoa(lim1--);
			ft_lstpush_back(&lst, tmp, ft_strlen(tmp) + 1);
			free(tmp);
		}
	return (lst);
}

static t_list	*get_alpha_range(int lim1, int lim2, char **s)
{
	char	buf[3];
	t_list	*lst;

	lst = NULL;
	buf[0] = '\\';
	buf[2] = 0;
	if (lim1 < lim2)
		while (lim1 <= lim2)
		{
			buf[1] = lim1++;
			ft_lstpush_back(&lst, buf, 3);
		}
	else
		while (lim1 >= lim2)
		{
			buf[1] = lim1--;
			ft_lstpush_back(&lst, buf, 3);
		}
	*s += 6;
	return (lst);
}

t_list			*get_valid_range(char **s, int i)
{
	t_list	*lst;

	lst = NULL;
	if (ft_isprint((*s)[1]) && (*s)[1] != ',' && (*s)[2] == '.' && (*s)[3] ==
			'.' && ft_isprint((*s)[4]) && (*s)[4] != ',' && (*s)[5] == '}')
		lst = get_alpha_range((*s)[1], (*s)[4], s);
	else if ((ft_isdigit((*s)[i]) || (((*s)[i] == '+' || (*s)[i] == '-')
									&& ft_isdigit((*s)[i + 1]))) && i++)
	{
		while (ft_isdigit((*s)[i]))
			++i;
		if ((*s)[i] == '.' && (*s)[++i] == '.' && i++)
		{
			if ((*s)[i] == '+' || (*s)[i] == '-')
				++i;
			if (ft_isdigit((*s)[i]))
			{
				while (ft_isdigit((*s)[i]))
					++i;
				if ((*s)[i] == '}')
					lst = get_num_range(s);
			}
		}
	}
	return (lst);
}
