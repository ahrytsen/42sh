/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 12:44:11 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/22 17:54:57 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static int	check_class_vals(char *buf, char *buf_q, int *i, char c)
{
	int							j;
	static const t_char_class	class[] = {{"[:alnum:]", ft_isalnum},
			{"[:alpha:]", ft_isalpha}, {"[:ascii:]", ft_isascii},
			{"[:blank:]", ft_isblank}, {"[:cntrl:]", ft_iscntrl},
			{"[:digit:]", ft_isdigit}, {"[:graph:]", ft_isgraph},
			{"[:lower:]", ft_islower}, {"[:print:]", ft_isprint},
			{"[:punct:]", ft_ispunct}, {"[:space:]", ft_iswhitespace},
			{"[:upper:]", ft_isupper}, {"[:word:]", ft_isword},
			{"[:xdigit:]", ft_isxdigit}, {NULL, NULL}};

	j = -1;
	while (class[++j].name)
		if (ft_strnequ(class[j].name, buf + *i, ft_strlen(class[j].name)) &&
			!ft_strnchr(buf_q + *i, 1, (int)ft_strlen(class[j].name)))
		{
			*i += ft_strlen(class[j].name);
			return (class[j].func(c));
		}
	*i += 1;
	return (0);
}

static int	check_vals(char *buf, char *buf_q, char *brackets_end, char *str)
{
	int				i;
	char			j;
	const int		eq = (*buf == '!' || *buf == '^') && !*buf_q ? 0 : 1;

	i = eq ? 0 : 1;
	while (buf[i])
		if (buf[i] == '[' && buf[i + 1] == ':' && !buf_q[i] && !buf_q[i + 1])
		{
			if (check_class_vals(buf, buf_q, &i, *str))
				return (eq ? ft_regex_str(brackets_end + 1, str + 1, 0) : 0);
		}
		else if (buf[i + 1] == '-' && buf[i + 2] && !buf_q[i + 1] && (i += 3))
		{
			j = buf[i - 3] - 1;
			while (++j <= buf[i - 1])
				if (j == *str)
					return (eq ?
							ft_regex_str(brackets_end + 1, str + 1, 0) : 0);
		}
		else if (buf[i] == *str)
			return (eq ? ft_regex_str(brackets_end + 1, str + 1, 0) : 0);
		else
			++i;
	return (eq ? 0 : ft_regex_str(brackets_end + 1, str + 1, 0));
}

static void	get_vals(char *pattern, char *buf, char *buf_q, char *brackets_end)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (pattern != brackets_end)
	{
		if (*pattern == '\\' && !quote && !buf_q[i] && pattern++)
			buf_q[i] = 1;
		else if ((*pattern == '\'' || *pattern == '"') && !buf_q[i] && !quote)
			quote = *pattern++;
		else if ((*pattern == '\'' || *pattern == '"') && quote && !buf_q[i]
				&& pattern++)
			quote = 0;
		else
		{
			buf[i] = *pattern++;
			if (quote && !buf_q[i])
				buf_q[i] = 1;
			++i;
		}
	}
}

int			ft_regex_brackets(char *pattern, char *str, char q)
{
	char	*brackets_end;
	char	buf[ft_strlen(pattern) + 1];
	char	buf_q[ft_strlen(pattern) + 1];

	if ((brackets_end = check_brackets(pattern)))
	{
		ft_bzero(buf, sizeof(buf));
		ft_bzero(buf_q, sizeof(buf));
		get_vals(pattern, buf, buf_q, brackets_end);
		return (check_vals(buf, buf_q, brackets_end, str));
	}
	else if (*(pattern + 1) == ']' && *(pattern + 2) == '\0')
		return (0);
	else if (*pattern == *str)
		return (ft_regex_str(pattern + 1, str + 1, q));
	return (0);
}
