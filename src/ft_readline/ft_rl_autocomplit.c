/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomplit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:19:38 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:35:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

/*
**static char	*ft_search_files(char	*line)
**{
**	DIR				*dirp;
**	struct dirent	*dp;
**	int				len;
**	char			*path;
**
**	if (!line || (path = NULL))
**		return (NULL);
**	if (ft_strchr(line, '/'))
**	{
**		path = ft_strsub(line, 0, ft_strrchr(line, '/') - line + 1);
**		line = ft_strrchr(line, '/') + 1;
**	}
**	if (*path != '/' && ft_strncmp(path, "./", 2))
**		path = ft_strextend(ft_strdup("./"), path);
**	len = ft_strlen(line);
**	dirp = opendir(path);
**	while (dirp && (dp = readdir(dirp)))
**		if (!ft_strncmp(dp->d_name, line, len) && !closedir(dirp))
**		{
**			free(path);
**			return (ft_strdup(dp->d_name));
**		}
**	closedir(dirp);
**	free(path);
**	return (NULL);
**}
*/

static char	*ft_search_builtin(char *line)
{
	int					i;
	int					len;
	const static char	*builtins[] = {"echo", "cd", "fg", "setenv", "unsetenv",
									"env", "exit", NULL};

	i = 0;
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (builtins[i] && ft_strncmp(line, builtins[i], len))
		i++;
	return (builtins[i] ? ft_strdup(builtins[i]) : NULL);
}

static char	*ft_searchcmd(char *line)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				len;
	int				i;
	char			**path;

	if (!line || !(path = ft_strsplit(ft_getenv("PATH"), ':')))
		return (NULL);
	i = 0;
	len = ft_strlen(line);
	while (path[i])
	{
		dirp = opendir(path[i++]);
		while (dirp && (dp = readdir(dirp)))
			if (ft_strncmp(dp->d_name, line, len) == 0)
			{
				closedir(dirp);
				ft_strarr_free(path);
				return (ft_strdup(dp->d_name));
			}
		closedir(dirp);
	}
	ft_strarr_free(path);
	return (NULL);
}

void		ft_autocomplit(t_line *cursor)
{
	char	*line;
	char	*res;
	char	*tmp;

	res = NULL;
	line = NULL;
	if (get_term()->prompt == P_USER
		&& (line = line_tostr(&cursor, 0))
		&& ((res = ft_search_builtin(line))
			|| (res = ft_searchcmd(line))))
	{
		tmp = res + ft_strlen(line);
		while (*tmp && ft_printf("%c", *tmp))
			line_add(cursor, *tmp++);
		ft_printf(" ");
		line_add(cursor, ' ');
	}
	else
		ft_printf("\a");
	free(res);
	free(line);
}
