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

static void	rl_search_in_path(t_list **list, char *str, int i, size_t len)
{
	char			*path;
	char			part[NAMESIZE];
	DIR				*directory;
	struct dirent	*fl;
	char			*ptr;

	path = ft_getenv("PATH");
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
	rl_search_in_path(&list, str, 0, len);
	if (!list && write(0, "\a", 1))
		return (NULL);
	return (ft_rl_match_drawer(list, str));
}

static void	rl_loop_var(t_list **list, char **env, char *str, size_t len)
{
	char	*in;
	char	*ptr;
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(str, env[i], len))
		{
			in = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			ptr = ft_strjoin(in, " ");
			ft_lstadd_end(list, ft_lstnew((void *)ptr, ft_strlen(ptr) + 1));
			free(in);
			free(ptr);
		}
		i++;
	}
}

char		*ft_rl_search_varname(char *str, size_t len)
{
	t_list	*list;

	list = NULL;
	rl_loop_var(&list, get_environ()->envar, str, len);
	rl_loop_var(&list, get_environ()->shvar, str, len);
	if (!list && write(0, "\a", 1))
		return (NULL);
	return (ft_rl_match_drawer(list, str));
}
