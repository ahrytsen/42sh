/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:30:23 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/05 17:48:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

char	*skip_parentheses(char *s)
{
	while (*++s)
		if (*s == '\\')
			*(s + 1) ? ++s : 0;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == ')')
			break ;
		else if (*s == '(')
			s = skip_parentheses(s);
	return (s);
}

char	*skip_quotes(char *s)
{
	char	c;

	c = *s;
	while (*++s)
		if (*s == '\\' && c != '\'')
			*(s + 1) ? ++s : 0;
		else if (*s == '`' && c == '"')
			s = skip_quotes(s);
		else if (*s == '$' && s[1] == '(' && c == '"')
			s = skip_parentheses(s + 1);
		else if (*s == c)
			break ;
	return (s);
}

char	*check_braces(char *s)
{
	while (*++s)
		if (*s == '\\')
			*(s + 1) ? ++s : 0;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '$' && *(s + 1) == '(')
			s = skip_parentheses(s + 1);
		else if (*s == '}')
			break ;
		else if (*s == '{')
			s = check_braces(s);
	return (s);
}

int		check_comma(char *s)
{
	int		comma;

	comma = 0;
	while (*++s)
		if (*s == ',')
			comma = 1;
		else if (*s == '\\')
			*(s + 1) ? ++s : 0;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '$' && s[1] == '(')
			s = skip_parentheses(s + 1);
		else if (*s == '}')
			break ;
		else if (*s == '{')
			s = check_braces(s);
	return (comma);
}
