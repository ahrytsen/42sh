/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:39:53 by dlinkin           #+#    #+#             */
/*   Updated: 2018/09/05 18:02:28 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

static size_t	cut_wrds(char *str, char c)
{
	size_t	i;
	char	q;

	i = 0;
	while (*str)
	{
		while (*str && *str != c)
			if (*str == '\\')
				*++str ? str++ : 0;
			else if (ft_strchr("'\"", *str) && (q = *str++))
			{
				while (*str && *str != q)
					if (*str == '\\' && q != '\'')
						*++str ? str++ : 0;
					else
						str++;
				*str ? str++ : 0;
			}
			else
				++str;
		i++;
		while (*str == c)
			str++;
	}
	return (i);
}

static void		*cut_free(char **out)
{
	int i;

	i = 0;
	while (out[i])
	{
		free(out[i]);
		i++;
	}
	free(out);
	return (NULL);
}

static char		*cut_word(char const *s, size_t i)
{
	char *out;

	out = (char *)malloc(sizeof(char) * i + 1);
	out[i] = '\0';
	while (i)
	{
		out[i - 1] = *(s + i - 1);
		i--;
	}
	return (out);
}

static size_t	skip_quote(char *s, size_t i)
{
	char	q;

	q = *(s + i++);
	while (*(s + i) != q && *(s + i))
		if (q != '\'' && s[i] == '\\')
			s[++i] ? i++ : 0;
		else
			++i;
	return (i + 1);
}

char			**ft_strcut(char *s, char c)
{
	char	**out;
	size_t	i;
	size_t	j;

	j = cut_wrds(s, c);
	if (!j || !(out = (char**)malloc(sizeof(char*) * j + 1)))
		return (NULL);
	j = 0;
	while (*s)
	{
		i = 0;
		while (*(s + i) != c && *(s + i))
			if (*(s + i) == '\\')
				s[++i] ? i++ : 0;
			else
				i = *(s + i) && ft_strchr("'\"", *(s + i)) ?
					skip_quote(s, i) : i + 1;
		if (!(out[j++] = cut_word(s, i)))
			return (cut_free(out));
		s += i;
		while (*s == c)
			s++;
	}
	out[j] = NULL;
	return (out);
}
