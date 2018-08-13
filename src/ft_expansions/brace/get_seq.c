/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_seq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:37:26 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/13 14:57:27 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static char	*get_braces_elem(char *s, char *buf, int *i, t_list **lst)
{
	int		j;
	t_list	*vals;
	t_list	*tmp;

	vals = NULL;
	s = get_brace_seq(&s, &vals);
	tmp = vals;
	while (vals->next)
	{
		j = *i;
		put_str_to_buf(buf, &j, vals->content);
		get_one_elem(s, buf, lst);
		ft_bzero(buf + *i, ft_strlen(buf + *i));
		vals = vals->next;
	}
	put_str_to_buf(buf, i, vals->content);
	ft_lstdel(&tmp, (void (*)(void *, size_t))free);
	return (s);
}

char		*get_one_elem(char *s, char *buf, t_list **lst)
{
	int		i;

	i = ft_strlen(buf);
	while (*s)
		if (*s == ',')
		{
			++s;
			break ;
		}
		else if (*s == '}')
			break ;
		else if (*s && ft_strchr("\"'`", *s))
			s = put_quote_content_to_buf(buf, &i, s);
		else if (*s == '\\')
			s = put_backslash_to_buf(buf, &i, s);
		else if (*s == '(')
			s = put_parentheses_content_to_buf(buf, &i, s);
		else if (*s == '{')
			s = get_braces_elem(s, buf, &i, lst);
		else
			buf[i++] = *s++;
	ft_lstpush_back(lst, buf, i + 1);
	return (s);
}

char		*get_brace_seq(char **s, t_list **lst)
{
	char	buf[ft_strlen(*s) + 1];
	char	*tmp;

	if ((*lst = get_valid_range(s, 1)))
		return (*s);
	else if (!check_comma(*s))
	{
		*lst = NULL;
		return (*s);
	}
	tmp = *s + 1;
	while (*tmp && *tmp != '}')
	{
		ft_bzero(buf, ft_strlen(*s));
		tmp = get_one_elem(tmp, buf, lst);
	}
	if (*(tmp - 1) == ',')
		ft_lstpush_back(lst, "\0", 2);
	return (*tmp ? ++tmp : tmp);
}
