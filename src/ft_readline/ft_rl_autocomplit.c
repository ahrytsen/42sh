/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomplit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:27:47 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/01 14:27:48 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

char		*ft_rl_autocomp_switcher(t_list *lst, char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (i != get_term()->comp_stage)
	{
		i++;
		lst = lst->next;
	}
	get_term()->comp_stage++;
	if (lst->next == NULL)
		get_term()->comp_stage = 0;
	get_term()->comp_erase = ft_strlen_unicode(lst->content)
			- (ft_strlen_unicode(str) + 1);
	i = lst->content_size - (ft_strlen(str) + 2);
	ptr = (char *)ft_memalloc(i + 1);
	ft_strncpy(ptr, lst->content + ft_strlen(str), i);
	return (ptr);
}

static char	*rl_check_line(t_line *cur, size_t size)
{
	char	*line;
	t_line	*tmp;

	tmp = cur;
	while (cur && cur->next && !ft_isseparator(cur->ch)
		&& (cur->ch != '$' || (cur->ch == '$' && size == 1)))
	{
		cur = cur->next;
		size += ft_strlen((char*)&cur->ch);
		ft_curright(1);
	}
	get_term()->cursor = cur;
	while (tmp->prev && tmp->prev->ch != ';' && tmp->prev->ch != '&'
		&& tmp->prev->ch != '|' && (tmp = tmp->prev))
		size += ft_strlen((char*)&tmp->ch);
	if (!(line = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	while (tmp != cur)
	{
		ft_strcat(line, (char*)&tmp->ch);
		tmp = tmp->next;
	}
	return (line);
}

static char	*rl_search(char *str)
{
	char	*s;
	size_t	len;
	int		mk;

	len = ft_strlen(str);
	while (len && !ft_isseparator(str[len - 1]) && str[len] != '$')
		len--;
	s = str + len;
	while (len && (str[len - 1] == ' ' || str[len - 1] == '\t')
		&& str[len - 1] != ';' && str[len - 1] != '|' && str[len - 1] != '&')
		len--;
	mk = ((!len || str[len - 1] == ';' || str[len - 1] == '|'
			|| str[len - 1] == '&') ? 1 : 0);
	if (mk && *s != '~' && *s != '$' && *s != '.' && *s != '/' && *s != '!')
		return (ft_rl_search_command(s, ft_strlen(s)));
	if (*s == '$')
		return (ft_rl_search_varname(s + 1, ft_strlen(s) - 1));
	return (ft_rl_search_filename(s, ft_strlen(s)));
}

void		ft_autocomplit(t_line *cursor)
{
	char	*line;
	char	*res;
	char	*tmp;

	line = NULL;
	if (get_term()->comp_stage > -1)
		while (get_term()->comp_erase--)
			ft_back_space();
	else
		get_term()->comp_erase = 0;
	if (get_term()->prompt == P_USER && (line = rl_check_line(cursor, 1)))
	{
		if ((res = rl_search(line)))
		{
			tmp = res;
			while (*res)
				ft_add(ft_get_unichar(&res));
			free(tmp);
		}
	}
	else
		write(1, "\a", 1);
	free(line);
}
