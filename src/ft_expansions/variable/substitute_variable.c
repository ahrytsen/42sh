/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 08:15:32 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/23 11:49:49 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

char	*record_var(t_buf **buf, char *s)
{
	char	*tmp;

	tmp = NULL;
	if (ft_isdigit(*s) && *s - 48 <= get_environ()->argc)
		ft_putstr_mshbuf(buf, get_environ()->argv[*s++ - 48], -1);
	else if (*s == '?' && ++s)
	{
		tmp = ft_itoa(get_environ()->st);
		ft_putstr_mshbuf(buf, tmp, -1);
	}
	else if  (*s == '$' && ++s)
	{
		tmp = ft_itoa(get_environ()->sh_pid);
		ft_putstr_mshbuf(buf, tmp, -1);
	}
	else
	{
		tmp = s;
		while (ft_isword(*s))
			++s;
		tmp = ft_strsub(tmp, 0, s - tmp);
		ft_putstr_mshbuf(buf, ft_getenv(tmp), -1);
	}
	free(tmp);
	return (s);
}

void	substitute_variable(t_list *lst)
{
	char	*s;
	t_buf	*buf;
	t_buf	*head;

	s = lst->content;
	if (!(buf = ft_memalloc(sizeof(t_buf))))
		return;
	head = buf;
	while (*s)
		if (*s == '\\' && s++)
			ft_slash(&buf, &s);
		else if (*s == '$' && ft_isword(*(s + 1)) && s++)
			s = record_var(&buf, s);
		else if (*s == '\'' && s++)
			ft_quote(&buf, &s);
		else
			ft_putchar_mshbuf(&buf, *s++);
	free(lst->content);
	lst->content = ft_buftostr(head);
}
