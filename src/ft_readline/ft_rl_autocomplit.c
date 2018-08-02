/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:27:47 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/01 14:27:48 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static char		*ft_rl_search_varname(char *str, size_t len)
{
	t_list	*list;
	char	**env;
	char	*in;
	int		i;

	list = NULL;
	env = get_environ()->env;
	i = -1;
	while (env && env[++i])
		if (!ft_strncmp(str, env[i], len))
		{
			in = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			ft_lstadd_end(&list, ft_lstnew((void *)in, ft_strlen(in) + 1));
			free(in);
		}
	// env = get_environ()->shvar;
	// i = -1;
	// while (env && env[++i])
	// 	if (!ft_strncmp(str, env[i], len))
	// 	{
	// 		in = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
	// 		ft_lstadd_end(&list, ft_lstnew((void *)in, ft_strlen(in) + 1));
	// 		free(in);
	// 	}
	return (ft_rl_match_drawer(list, str));
}

static char	*rl_check_line(t_line *cur)
{
	char	*line;
	size_t	size;
	t_line	*tmp;

	tmp = cur;
	size = 1;
	while (cur && cur->next && cur->ch != ' ' && cur->ch != '\t'
		&& (cur->ch != '$' || (cur->ch == '$' && size == 1)) && cur->ch != ';'
		&& cur->ch != '&' && cur->ch != '|')
	{
		cur = cur->next;
		size += ft_strlen((char*)&cur->ch);
	}
	while (tmp->prev && tmp->prev->ch != ';' && tmp->prev->ch != '&'
		&& tmp->prev->ch != '|')
	{
		tmp = tmp->prev;
		size += ft_strlen((char*)&tmp->ch);
	}
	if (!(line = ft_memalloc(sizeof(char) * size)))
		return (NULL);
	while (tmp != cur)
	{
		ft_strcat(line, (char*)&tmp->ch);
		tmp = tmp->next;
	}
	return (line);
}

static int	rl_zeroed(char *str, size_t len)
{
	while (len && (str[len - 1] == ' ' || str[len - 1] == '\t')
		&& str[len - 1] != ';' && str[len - 1] != '|' && str[len - 1] != '&')
		len--;
	if (!len || str[len - 1] == ';' || str[len - 1] == '|'
		|| str[len - 1] == '&')
		return (1);
	return (0);
}

static char	*rl_search(char *str)
{
	char	*s;
	size_t	len;

	len = ft_strlen(str);
	while (len && str[len - 1] != ' ' && str[len - 1] != '\t' && str[len] != '$'
		&& str[len - 1] != ';' && str[len - 1] != '|' && str[len - 1] != '&')
		len--;
	s = str + len;
	if (rl_zeroed(s, len) && *s != '~' && *s != '$' && *s != '.'
		&& *s != '/' && *s != '!')
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
	if (get_term()->prompt == P_USER && (line = rl_check_line(cursor)))
	{
		if ((res = rl_search(line)))
		{
			tmp = res;
			while (*res && write(1, res, 1))
				line_add(cursor, *res++);
			write(1, " ", 1);
			line_add(cursor, ' ');
			free(tmp);
		}
	}
	else
		write(1, "\a", 1);
	free(line);
}
