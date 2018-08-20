/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 16:40:23 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/20 12:43:21 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

void	print_lst(t_list *lst) //TODO: delete
{
	while (lst)
	{
		ft_printf(lst->next ? "%s " : "%s\n", lst->content);
		lst = lst->next;
	}
}

int		ft_regex_str(char *pattern, char *str, char q)
{
	int		sl;

	sl = 0;
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '\\' && pattern++)
		sl = 1;
	else if ((*pattern == '\'' || *pattern == '"') && !q)
		q = *pattern++;
	else if (*pattern == q)
	{
		q = 0;
		++pattern;
	}
	if (!q && !sl && *pattern == '[' && *str)
		return (ft_regex_brackets(pattern + 1, str, q));
	if (!q && !sl && *pattern == '*' && *str)
		return (ft_regex_str(pattern + 1, str, q) || ft_regex_str(pattern, str + 1, q));
	if (!q && !sl && *pattern == '*' && !*str)
		return (ft_regex_str(pattern + 1, str, q));
	if ((!q && !sl && (*pattern == '?' && *str)) || (*pattern == *str))
		return (ft_regex_str(pattern + 1, str + 1, q));
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

int		main(int ac, char **av)
{
	char	**names;
	char	path[1024];
	t_list	*list;
	char	*pattern;

	pattern = av[1] ? av[1] : "file";
	names = ft_strcut(pattern, '/');
	list = NULL;
	if (*pattern != '/')
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
	list ? print_lst(list) : ft_printf("%s\n", pattern);
//	return (list);
	return (0);
}
