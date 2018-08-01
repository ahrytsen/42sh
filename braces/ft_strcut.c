/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:39:53 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/01 16:28:27 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cut_wrds(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		while (*str && *str != c)
			str++;
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

char			**ft_strcut(char const *s, char c)
{
	char	**out;
	size_t	n;
	size_t	i;
	size_t	j;

	n = cut_wrds(s, c);
	if (!n || !(out = (char**)malloc(sizeof(char*) * n + 1)))
		return (NULL);
	j = 0;
	while (*s)
	{
		i = 0;
		while (*(s + i) != c && *(s + i))
			i++;
		if (!(out[j] = cut_word(s, i)))
			return (cut_free(out));
		j++;
		s += i;
		while (*s == c)
			s++;
	}
	out[j] = NULL;
	return (out);
}
