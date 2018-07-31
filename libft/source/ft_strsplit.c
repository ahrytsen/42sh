/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:24:12 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/31 13:24:15 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		while (*str == c)
			str++;
		if (*str != '\0')
		{
			while (*str != c && *str != '\0')
				str++;
			i++;
		}
	}
	return (i);
}

static int		ft_free(char **out)
{
	int i;

	i = 0;
	while (out[i])
	{
		free(out[i]);
		i++;
	}
	free(out);
	return (1);
}

static char		**ft_apozh(char const *s, char c, size_t j, size_t k)
{
	char	**out;
	size_t	i;

	out = (char**)malloc(sizeof(char*) * ft_words(s, c) + 1);
	if (!out)
		return (NULL);
	while (s[k])
	{
		i = 0;
		while (s[k + i] != c && s[k + i] != '\0')
			i++;
		if (i && (out[j] = (char*)malloc(sizeof(char) * i)))
		{
			if (!out[j] && (ft_free(out)))
				return (NULL);
			i = 0;
			while ((out[j][i] = s[k + i]) && s[k + i + 1]
			!= c && s[k + i + 1] != '\0')
				i++;
			out[j++][i + 1] = '\0';
		}
		k += ++i;
	}
	out[j] = 0;
	return (out);
}

char			**ft_strsplit(char const *s, char c)
{
	if (s)
	{
		return (ft_apozh(s, c, 0, 0));
	}
	return (NULL);
}
