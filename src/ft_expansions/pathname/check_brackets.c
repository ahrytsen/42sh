/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 12:59:27 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/20 13:34:42 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static char	*check_class(char *pattern)
{
	int					i;
	static const char	*class[] = {"[:alnum:]", "[:alpha:]", "[:ascii:]",
							"[:blank:]", "[:cntrl:]", "[:digit:]", "[:graph:]",
							"[:lower:]", "[:print:]", "[:punct:]", "[:space:]",
							"[:upper:]", "[:word:]", "[:xdigit:]", NULL};

	i = -1;
	while (class[++i])
		if (ft_strnequ(class[i], pattern, ft_strlen(class[i])))
			return (pattern + ft_strlen(class[i]) - 1);
	return (0);
}

char		*check_brackets(char *pattern)
{
	char	quote;
	char	*tmp;

	pattern += *pattern == '^' || *pattern == '!' ? 1 : 0;
	pattern += *pattern == ']' ? 1 : 0;
	while (*pattern)
	{
		if (*pattern == ']')
			return (pattern);
		else if (*pattern == '[' && *(pattern + 1) == ':' &&
				(tmp = check_class(pattern)))
			pattern = tmp;
		else if (*pattern == '\\')
			++pattern;
		else if (*pattern == '\'' || *pattern == '"')
		{
			quote = *pattern++;
			while (*pattern != quote)
				++pattern;
		}
		++pattern;
	}
	return (0);
}
