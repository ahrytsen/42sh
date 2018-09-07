/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomp_cmd_and_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:27:12 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/02 15:27:12 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static int	rl_get_path_name(char *out, char *path, char *name)
{
	char	*tmp;
	int		ret;

	ft_bzero((void *)out, NAMESIZE);
	if (!(tmp = ft_strchr(path, ':')))
	{
		ret = ft_strlen(path);
		ft_strncpy(out, path, ret);
	}
	else
	{
		if (*path == 0)
			return (0);
		ft_strncpy(out, path, tmp - path);
		ret = tmp - path;
	}
	ft_strcat(out, "/");
	ft_strcat(out, name);
	return (ret);
}

static void	rl_search_in_path(t_list **list, char *str, char *path, size_t len)
{
	char			part[NAMESIZE];
	DIR				*directory;
	struct dirent	*fl;
	char			*ptr;
	int				i;

	i = 0;
	while ((i = rl_get_path_name(part, path, "")))
	{
		if ((directory = opendir(part)))
		{
			while ((fl = readdir(directory)))
				if (fl->d_name[0] != '.' && !ft_strncmp(str, fl->d_name, len))
				{
					ptr = ft_strjoin(fl->d_name, " ");
					ft_lstadd_end(list, ft_lstnew((void *)ptr
					, ft_strlen(ptr) + 1));
					free(ptr);
				}
			closedir(directory);
		}
		path += i;
		if (*path)
			path++;
	}
}

char		*ft_rl_search_command(char *str, size_t len)
{
	t_list					*list;
	extern const t_builtins	g_builtin[];
	int						i;
	char					*ptr;

	i = 0;
	list = NULL;
	while (g_builtin[i].cmd)
	{
		if (!ft_strncmp(str, g_builtin[i].cmd, len))
		{
			ptr = ft_strjoin(g_builtin[i].cmd, " ");
			ft_lstadd_end(&list, ft_lstnew((void *)ptr, ft_strlen(ptr) + 1));
			free(ptr);
		}
		i++;
	}
	if ((ptr = ft_getenv("PATH")))
		rl_search_in_path(&list, str, ptr, len);
	if (!list && write(0, "\a", 1))
		return (NULL);
	return (ft_rl_match_drawer(ft_lstsort(list), str));
}

char		*ft_rl_search_varname(char *str, size_t len)
{
	t_list	*list;
	t_var	*tmp;
	char	*in;
	char	*ptr;

	list = NULL;
	tmp = get_environ()->shvar;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, str, len))
		{
			if ((ptr = ft_strchr(tmp->var, '=')))
				in = ft_strsub(tmp->var, 0, ptr - tmp->var);
			else
				in = ft_strdup(tmp->var);
			ptr = ft_strjoin(in, " ");
			ft_lstadd_end(&list, ft_lstnew((void *)ptr, ft_strlen(ptr) + 1));
			free(in);
			free(ptr);
		}
		tmp = tmp->next;
	}
	if (!list && write(0, "\a", 1))
		return (NULL);
	return (ft_rl_match_drawer(ft_lstsort(list), str));
}
