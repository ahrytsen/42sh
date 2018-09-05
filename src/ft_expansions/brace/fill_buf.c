/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:40:46 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/05 17:50:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

char	*put_backslash_to_buf(char *buf, int *i, char *s)
{
	buf[(*i)++] = *s++;
	if (*s)
		buf[(*i)++] = *s++;
	return (s);
}

char	*put_quote_content_to_buf(char *buf, int *i, char *s)
{
	char	quote;

	quote = *s;
	buf[(*i)++] = *s++;
	while (*s != quote && *s)
		if (*s == '\\' && quote != '\'')
			s = put_backslash_to_buf(buf, i, s);
		else if (*s == '`' && quote == '"')
			s = put_quote_content_to_buf(buf, i, s);
		else if (*s == '$' && s[1] == '(' && quote == '"')
		{
			buf[(*i)++] = *s++;
			s = put_parentheses_content_to_buf(buf, i, s);
		}
		else
			buf[(*i)++] = *s++;
	buf[(*i)++] = *s++;
	return (s);
}

char	*put_str_to_buf(char *buf, int *i, char *s)
{
	while (*s)
		buf[(*i)++] = *s++;
	return (s);
}

char	*put_parentheses_content_to_buf(char *buf, int *i, char *s)
{
	buf[(*i)++] = *s++;
	while (*s)
		if (*s == '\\')
			s = put_backslash_to_buf(buf, i, s);
		else if (*s && ft_strchr("\"'`", *s))
			s = put_quote_content_to_buf(buf, i, s);
		else if (*s == ')')
			break ;
		else if (*s == '(')
			s = put_parentheses_content_to_buf(buf, i, s);
		else
			buf[(*i)++] = *s++;
	buf[(*i)++] = *s++;
	return (s);
}
