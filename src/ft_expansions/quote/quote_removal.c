/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 03:23:42 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/25 06:26:39 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

void	remove_quotes(t_list *lst)
{
	char	*s;
	t_buf	*buf;
	t_buf	*head;

	s = lst->content;
	if (!(buf = ft_memalloc(sizeof(t_buf))))
		return ;
	head = buf;
	while (*s)
		if (*s == '\\' && *(s + 1) == 10)
			s += 2;
		else if (*s == '\\' && s++)
			ft_slash(&buf, &s);
		else if (*s == '\'' && s++)
			ft_quote(&buf, &s);
		else if (*s == '"' && s++)
			ft_dquote(&buf, &s);
		else
			ft_putchar_mshbuf(&buf, *s++);
	free(lst->content);
	lst->content = ft_buftostr(head);
}
