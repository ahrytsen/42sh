/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 13:31:09 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/13 16:18:27 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

void		print_lst(t_list *lst) //TODO: delete
{
	while (lst)
	{
		ft_printf("%s ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

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

int 	main(int ac, char **av)
{
	(void)ac;
	if (!av[1])
	{
		char buf[500];
		char *s = "{,{1..2},{10..20},{a..z},{A..Z}}pre{,{1..2},{10..20},{a..z},{A..Z}}file{,{1..2},{10..20},{a..z},{A..Z}}post{,{1..2},{10..20},{a..z},{A..Z}}";
		t_list *lst = NULL;
		ft_bzero(buf, 500);
		print_lst((lst = expand_braces(s, 0, buf)));
		ft_lstdel(&lst, (void (*)(void *, size_t))free);
	}
	else
	{
		char buf[ft_strlen(av[1]) + 1];
		ft_bzero(buf, ft_strlen(av[1]) + 1);
		print_lst(expand_braces(av[1], 0, buf));
	}
	return (0);
}
