/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:40:23 by dlinkin           #+#    #+#             */
/*   Updated: 2018/09/05 17:56:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

int			ft_regex_str(char *pat, char *str, char q)
{
	int		sl;

	sl = 0;
	if (!*pat && !*str)
		return (1);
	if (*pat == '\\' && pat++)
		sl = 1;
	else if ((*pat == '\'' || *pat == '"') && !q)
		q = *pat++;
	else if (*pat == q)
	{
		q = 0;
		++pat;
	}
	if (!q && !sl && *pat == '[' && *str)
		return (ft_regex_brackets(pat + 1, str, q));
	if (!q && !sl && *pat == '*' && *str)
		return (ft_regex_str(pat + 1, str, q) || ft_regex_str(pat, str + 1, q));
	if (!q && !sl && *pat == '*' && !*str)
		return (ft_regex_str(pat + 1, str, q));
	if ((!q && !sl && (*pat == '?' && *str)) || (*pat == *str))
		return (ft_regex_str(pat + 1, str + 1, q));
	return (0);
}

static int	compare_mthfkr_d_u_speak_it(char *a, char *b)
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

static void	recurcive(t_list **list, char *path, char **names, char *directory)
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
			if (!*(names + 1) && (S_ISREG(st.st_mode) || S_ISDIR(st.st_mode)))
				ft_lstpush_back(list, name, ft_strlen(name) + 1);
			else if (S_ISDIR(st.st_mode))
				recurcive(list, ft_strcat(name, "/"), names + 1, name);
			name[ft_strlen(path)] = 0;
		}
	closedir(papka);
}

static int	check_pathname(char *s)
{
	char	q;

	while (*s)
		if (*s == '\\')
			*++s ? s++ : 0;
		else if (ft_strchr("'\"", *s))
		{
			q = *s++;
			while (*s && *s != q)
				if (*s == '\\' && q != '\'')
					*++s ? s++ : 0;
				else
					s++;
			*s ? s++ : 0;
		}
		else if (*s == '*' || *s == '?' || *s == '[')
			return (1);
		else
			++s;
	return (0);
}

t_list		*expand_pathname(t_list *lst)
{
	char	**names;
	char	path[1024];
	t_list	*list;

	if (!check_pathname(lst->content))
		return (NULL);
	names = ft_strcut(lst->content, '/');
	list = NULL;
	if (*(char *)lst->content != '/')
	{
		path[0] = 0;
		recurcive(&list, path, names, ".");
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
