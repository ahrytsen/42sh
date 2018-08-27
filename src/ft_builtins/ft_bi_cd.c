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

static char	*path_resolver(char *old)
{
	char	*new;
	char	*ptr;
	char	**elem;
	int		i;

	new = (char *)ft_memalloc(ft_strlen(old) + 1);
	elem = ft_strsplit(old, '/');
	i = 0;
	while (elem[i])
	{
		if (!ft_strcmp(elem[i], "..") && (ptr = ft_strrchr(new, '/')))
		{
			while (*ptr)
			{
				*ptr = 0;
				ptr++;
			}
		}
		else if (ft_strcmp(elem[i], ".") && ft_strcmp(elem[i], ".."))
		{
			ft_strcat(new, "/");
			ft_strcat(new, elem[i]);
		}
		i++;
	}
	free(old);
	return (new);
}

static int	step2(char *curpath, char fl)
{
	char *str;
	struct stat	tmp;

	write(1, "@", 1);
	if (fl != 'P')
	{
		if (*curpath != '/')
		{
			str = ft_strjoin(ft_getenv("PWD"), "/");
			curpath = ft_strjoin(str, curpath);
			free(str);
		}
		curpath = path_resolver(curpath);
	}
	if (*curpath)
	{
		if ((access(curpath, F_OK)
		&& ft_dprintf(2, "cd: no such file or directory: %s\n", curpath))
		|| (!stat(curpath, &tmp)
		&& !S_ISDIR(tmp.st_mode) && ft_dprintf(2, "cd: not a directory: %s\n", curpath))
		|| (((access(curpath, X_OK)) || chdir(curpath) == -1)
		&& ft_dprintf(2, "cd: permission denied: %s\n", curpath)))
		return (256);
	}
	return (0);
}

static char	*search_cdpath(char *dir, char **paths)
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
	int		rat;

	fl = 'L';
	if (!(av = ft_cd_flags(av, &fl)))
		return (256);
	if (!*av && !(dir = ft_getenv("HOME")))
	{
		write(2, "cd: HOME not set\n", 17);
		return (256);
	}
	else if (*av && **av == '-' && !*(*av + 1) && !(dir = ft_getenv("OLDPWD"))
	&& write(2, "cd: OLDPWD not set\n", 19))
		return (256);
	else
		dir = *av;
	ft_printf("%s\n", dir);
	if (*dir == '/' || (!ft_strncmp(dir, "./", 2) || !ft_strncmp(dir, "../", 3)))
	{
		write(1, "#", 1);
		return (step2(dir, fl));
	}
	dir = search_cdpath(dir, ft_strsplit(ft_getenv("CDPATH"), ':'));
	rat = step2(dir, fl);
	free(dir);
	return (rat);
}
