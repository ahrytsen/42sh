/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:40:23 by dlinkin           #+#    #+#             */
/*   Updated: 2018/07/26 16:40:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <dirent.h>
#include <sys/stat.h>

char	**ft_strcut(char const *s, char c);

int		ft_regex_str(char *pattern, char *str, int i)
{
	int	sl;

	if (!*pattern && !*str)
		return (1);
	sl = 0;
	if (*pattern == '\\')
	{
		pattern++;
		sl = 1;
	}
	if (!sl && *pattern == '*' && *str)
	{
		return (ft_regex_str(pattern + 1, str, i + 1)
			|| ft_regex_str(pattern, str + 1, i + 1));
	}
	if (!sl && *pattern == '*' && !*str)
		return (ft_regex_str(pattern + 1, str, i + 1));
	if ((!sl && *pattern == '?' && *str) || (*pattern == *str))
		return (ft_regex_str(pattern + 1, str + 1, i + 1));
	return (0);
}

int		compare_mthfkr_d_u_speak_it(char *a, char *b)
{
	if ((a[0] != '.'
	|| (a[0] == '.' && b[0] == '.' && ft_strcmp(a, "..") && ft_strcmp(a, "."))
	|| (!ft_strcmp(a, "..") && !ft_strcmp(b, "..")))
	&& ft_regex_str(b, a, 0))
	{
		return (1);
	}
	return (0);
}

void	recurcive(t_list **list, char *path, char **names, char *directory)
{
	DIR				*papka;
	struct dirent	*file;
	struct stat		st;
	char			name[1024];

	if (!(papka = opendir(directory)))
		return ;
	name[0] = 0;
	ft_strcat(name, path);
	while ((file = readdir(papka)))
		if (compare_mthfkr_d_u_speak_it(file->d_name, *names))
		{
			ft_strcat(name, file->d_name);
			stat(name, &st);
			if (!*(names + 1))
				ft_lstpushback(list, ft_lstnew(name, ft_strlen(name)));
			else if (S_ISDIR(st.st_mode))
				recurcive(list, ft_strcat(name, "/"), names + 1, name);
			name[ft_strlen(path)] = 0;
		}
	closedir(papka);
}

t_list		*regex(char *pattern)
{
	char	**names;
	char	path[1024];
	t_list	*list;

	names = ft_strcut(av[1], '/');
	list = NULL;
	if (*pattern != '/' && *pattern != '~')
	{
		path[0] = 0;
		recurcive(&list, path, names, ".");
	}
	else if (*pattern != '/')
	{
		ft_strcat(path, getenv("HOME"));
		ft_strcat(path, "/");
		recurcive(&list, path, names + 1, getenv("HOME"));
	}
	else
	{
		path[0] = '/';
		path[1] = 0;
		recurcive(&list, path, names + 1, "/");
	}
	list = ft_lstsort(list);
	ft_free_arr((void **)names);
	return (list);
}
