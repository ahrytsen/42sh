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

static char	*ft_cd_getpath(char **av)
{
	char	*tmp;
	char	*next_path;

	tmp = NULL;
	next_path = NULL;
	if (*av && ft_strequ(*av, "-"))
		tmp = "OLDPWD";
	else if (!*av)
		tmp = "HOME";
	else
		next_path = *av;
	(!next_path && tmp) ? next_path = ft_getenv(tmp) : 0;
	(!next_path) ? ft_dprintf(2, "cd: %s not set\n", tmp) : 0;
	return (next_path);
}

static char	**ft_cd_flags(char **av, char *fl)
{
	int	i;

	while (*av && **av == '-' && *(*av + 1))
	{
		i = 1;
		if (ft_strequ(*av, "--"))
		{
			av++;
			break ;
		}
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

int			ft_cd(char **av)
{
	char		fl;
	char		*next_path;
	char		curent_path[MAXPATHLEN];
	struct stat	tmp;

	fl = 'L';
	if (!(av = ft_cd_flags(av, &fl)))
		return (256);
	if (!(next_path = ft_cd_getpath(av)))
		return (256);
	if ((next_path && access(next_path, F_OK)
		&& ft_dprintf(2, "cd: no such file or directory: %s\n", next_path))
		|| (next_path && !stat(next_path, &tmp) && !S_ISDIR(tmp.st_mode)
			&& ft_dprintf(2, "cd: not a directory: %s\n", next_path))
		|| (((next_path && access(next_path, X_OK)) || chdir(next_path) == -1)
			&& ft_dprintf(2, "cd: permission denied: %s\n", next_path)))
		return (256);
	if (*av && ft_strequ(*av, "-"))
		ft_printf("%s\n", next_path);
	ft_setenv("OLDPWD", ft_getenv("PWD"), 1);
	getcwd(curent_path, MAXPATHLEN);
	ft_setenv("PWD", curent_path, 1);
	return (0);
}
