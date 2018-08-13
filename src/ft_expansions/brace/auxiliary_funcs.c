/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:30:23 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/13 14:35:22 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

char	*skip_quotes(char *s)
{
	char	c;

	c = *s;
	while (*++s)
		if (*s == '\\')
			++s;
		else if (*s == c)
			break ;
	return (s);
}

char	*check_braces(char *s)
{
	while (*++s)
		if (*s == '\\')
			++s;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
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
			++s;
		else if (*s && ft_strchr("\"'`", *s))
			s = skip_quotes(s);
		else if (*s == '}')
			break ;
		else if (*s == '{')
			s = check_braces(s);
	return (comma);
}
