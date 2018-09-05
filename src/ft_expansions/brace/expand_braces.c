/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:31:09 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/05 16:04:37 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static char	*utilize_seq(char *buf, char *s, int *i, t_list **ret)
{
	t_list	*vals;
	t_list	*tmp;
	int		j;

	vals = NULL;
	s = get_brace_seq(&s, &vals);
	if (!(tmp = vals))
	{
		buf[(*i)++] = *s++;
		return (s);
	}
	while (vals->next)
	{
		j = *i;
		put_str_to_buf(buf, &j, vals->content);
		ft_lstadd_end(ret, expand_braces(s, j, buf));
		ft_bzero(buf + *i, ft_strlen(buf + *i));
		vals = vals->next;
	}
	put_str_to_buf(buf, i, vals->content);
	ft_lstdel(&tmp, (void (*)(void *, size_t))free);
	return (s);
}

t_list		*expand_braces(char *s, int i, char *buf)
{
	t_list	*ret;

	ret = NULL;
	while (*s)
		if (*s == '\\')
			s = put_backslash_to_buf(buf, &i, s);
		else if (*s && ft_strchr("\"'`", *s))
			s = put_quote_content_to_buf(buf, &i, s);
		else if (*s == '(')
			s = put_parentheses_content_to_buf(buf, &i, s);
		else if (*s == '{' && *check_braces(s) == '}')
			s = utilize_seq(buf, s, &i, &ret);
		else
			buf[i++] = *s++;
	ft_lstpush_back(&ret, buf, i + 1);
	return (ret);
}

t_list		*brace_expansion(t_list *lst)
{
	char	buf[lst->content_size];
	t_list	*new_lst;

	ft_bzero(buf, lst->content_size);
	new_lst = expand_braces(lst->content, 0, buf);
	if (!new_lst->next && ft_strequ(new_lst->content, lst->content))
	{
		free(new_lst->content);
		free(new_lst);
		return (NULL);
	}
	return (new_lst);
}
