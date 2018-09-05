/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 06:54:59 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/05 17:40:36 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static char		*skip_quote(char *s, size_t *res)
{
	const char	quote = *s++;

	++*res;
	while (*s && *s != quote)
		if (*s == '\\' && quote != '\'')
		{
			++s;
			++*res;
			if (*s && s++)
				++*res;
		}
		else
		{
			++s;
			++*res;
		}
	if (*s)
	{
		++s;
		++*res;
	}
	return (s);
}

static size_t	ft_strlen_c_quoted(char *s)
{
	size_t res;

	res = 0;
	while (!ft_strchr(" \n\t", *s))
		if (*s == '\\')
		{
			++s;
			++res;
			if (*s)
			{
				++s;
				++res;
			}
		}
		else if (ft_strchr("\"'", *s))
			s = skip_quote(s, &res);
		else
		{
			s++;
			res++;
		}
	return (res);
}

static t_list	*ft_strsplit_quoted(char *s)
{
	size_t	wlen;
	t_list	*lst;
	t_list	*beg;

	beg = NULL;
	while (*s)
	{
		if (!ft_strchr(" \t\n", *s))
		{
			wlen = ft_strlen_c_quoted(s);
			if ((lst = ft_lstpush_back(&beg, s, wlen + 1)))
				((char *)(lst->content))[lst->content_size - 1] = 0;
			s += wlen;
		}
		else
			s++;
	}
	return (beg);
}

t_list			*field_splitting(t_list *lst)
{
	return (ft_strsplit_quoted(lst->content));
}
