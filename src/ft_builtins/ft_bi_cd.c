/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:13:47 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:20:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	**ft_cd_flags(char **av, char *fl)
{
	int	i;

	while (*av && **av == '-' && *(*av + 1))
	{
		if (ft_strequ(*av, "--"))
		{
			av++;
			break ;
		}
		i = 1;
		while ((*av)[i])
		{
			if ((*av)[i] == 'L' || (*av)[i] == 'P')
				*fl = (*av)[i];
			else
			{
				ft_dprintf(2, "cd: -%c: invalid option\n"
							"cd: usage: cd [-L|-P] [dir]\n", (*av)[i]);
				return (NULL);
			}
			i++;
		}
		av++;
	}
	return (av);
}

static char	*path_resolver(char *ptr)
{
	char	*new;
	char	**elem;
	int		i;

	if (!*(ptr + 1))
		return (ptr);
	new = (char *)ft_memalloc(ft_strlen(ptr) + 1);
	elem = ft_strsplit(ptr, '/');
	free(ptr);
	i = 0;
	while (elem[i])
	{
		if (!ft_strcmp(elem[i], "..") && (ptr = ft_strrchr(new, '/')))
		{
			ft_bzero((void *)ptr, ft_strlen(ptr));
			!*new ? *new = '/' : 0;
		}
		else if (ft_strcmp(elem[i], ".") && ft_strcmp(elem[i], ".."))
			ft_strcat(ft_strcat(new, "/"), elem[i]);
		i++;
	}
	ft_free_arr((void **)elem);
	return (new);
}

static int	ft_change_dir(char **curpath, char fl, char *dir)
{
	char		*str;
	char		buf[MAXPATHLEN];
	struct stat	tmp;

	if (fl < 'P')
	{
		if (**curpath != '/' && (str = ft_strjoin(ft_getenv("PWD"), "/")))
			*curpath = ft_strextend(str, *curpath);
		*curpath = path_resolver(*curpath);
	}
	if (!(*curpath && **curpath))
		return (0);
	if ((access(*curpath, F_OK) && ft_dprintf(2, "cd: no such file or direc\
tory: %s\n", dir)) || (!stat(*curpath, &tmp) && !S_ISDIR(tmp.st_mode)
	&& ft_dprintf(2, "cd: not a directory: %s\n", dir))
	|| (((access(*curpath, X_OK)) || chdir(*curpath) == -1)
	&& ft_dprintf(2, "cd: permission denied: %s\n", dir)))
		return (256);
	ft_set_tool("OLDPWD", ft_getenv("PWD"), 1, ENVAR);
	ft_set_tool("PWD", (fl >= 'P' ? getcwd(buf, MAXPATHLEN) : *curpath)
	, 1, ENVAR);
	if (fl != 'L' && fl != 'P')
		ft_printf("%s\n", *curpath);
	return (0);
}

static char	*search_cdpath(char *dir, char **paths, char *fl)
{
	char		*curpath;
	char		*str;
	struct stat	tmp;
	int			i;

	if (paths)
	{
		i = 0;
		while (paths[i])
		{
			str = ft_strjoin(paths[i], "/");
			curpath = ft_strjoin(str, dir);
			free(str);
			if (!stat(curpath, &tmp) && S_ISDIR(tmp.st_mode))
			{
				(*fl)++;
				ft_free_arr((void **)paths);
				return (curpath);
			}
			free(curpath);
			i++;
		}
		ft_free_arr((void **)paths);
	}
	return (ft_strdup(dir));
}

int			ft_cd(char **av)
{
	char	fl;
	char	*dir;
	char	*tmp;
	int		rat;

	fl = 'L';
	if (!(av = ft_cd_flags(av, &fl)))
		return (256);
	if (!*av || (*av && **av == '-' && !*(*av + 1)))
	{
		tmp = (!*av ? "HOME" : "OLDPWD");
		*av ? fl++ : 0;
		if (!(dir = ft_getenv(tmp)) && ft_dprintf(2, "cd: %s not set\n", tmp))
			return (256);
	}
	else
		dir = *av;
	if (*dir != '/' && ft_strncmp(dir, "./", 2) && ft_strncmp(dir, "../", 3)
	&& ft_strncmp(dir, ".\0", 2) && ft_strncmp(dir, "..\0", 3))
		tmp = search_cdpath(dir, ft_strsplit(ft_getenv("CDPATH"), ':'), &fl);
	else
		tmp = ft_strdup(dir);
	rat = ft_change_dir(&tmp, fl, *av);
	free(tmp);
	return (rat);
}
