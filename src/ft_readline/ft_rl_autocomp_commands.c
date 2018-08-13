/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomp_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:27:12 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/02 15:27:12 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static int		rl_get_path_name(char *out, char *path, char *name)
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

static void		rl_search_in_path(t_list **list, char *str, int i, size_t len)
{
	char			*path;
	char			part[NAMESIZE];
	DIR				*directory;
	struct dirent	*fl;

	path = ft_getenv("PATH");
	while ((i = rl_get_path_name(part, path, "")))
	{
		if ((directory = opendir(part)))
		{
			while ((fl = readdir(directory)))
			{
				if (fl->d_name[0] != '.' && !ft_strncmp(str, fl->d_name, len))
					ft_lstadd_end(list, ft_lstnew((void *)fl->d_name
					, ft_strlen(fl->d_name) + 1));
			}
			closedir(directory);
		}
		path += i;
		if (*path)
			path++;
	}
}

char			*ft_rl_search_command(char *str, size_t len)
{
	t_list					*list;
	extern const t_builtins	g_builtin[];
	int						i;

	i = 0;
	list = NULL;
	while (g_builtin[i].cmd)
	{
		if (!ft_strncmp(str, g_builtin[i].cmd, len))
			ft_lstadd_end(&list, ft_lstnew((void *)g_builtin[i].cmd
				, ft_strlen(g_builtin[i].cmd) + 1));
		i++;
	}
	rl_search_in_path(&list, str, 0, len);
	return (ft_rl_match_drawer(list, str));
}
