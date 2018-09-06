/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:27:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/04 16:43:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const t_builtins	g_builtin[] = {
	{"echo", &ft_echo},
	{"bg", &ft_bg},
	{"cd", &ft_cd},
	{"fg", &ft_fg},
	{"jobs", &ft_jobs},
	{"history", &ft_history},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"unset", &ft_unset},
	{"env", &ft_env},
	{"exit", &ft_exit},
	{"export", &ft_export},
	{"exec", &ft_exec},
	{"read", &ft_bi_read},
	{"alias", &ft_alias},
	{"unalias", &ft_unalias},
	{NULL, NULL}
};

static int	ft_exec_builtin(char **cmd)
{
	int						i;
	extern const t_builtins	g_builtin[];

	i = 0;
	while (g_builtin[i].cmd && ft_strcmp(cmd[0], g_builtin[i].cmd))
		i++;
	if (g_builtin[i].cmd)
	{
		if (get_environ()->setvar)
			ft_set_var(get_environ()->setvar, SHVAR);
		return (g_builtin[i].ft_builtin(cmd + 1));
	}
	return (-1);
}

int			ft_exec_bypath(char **cmd, char *path, int bg)
{
	struct stat	tmp;
	int			fd;

	if (path && !access(path, F_OK) && !access(path, X_OK)
		&& !stat(path, &tmp) && S_ISREG(tmp.st_mode))
	{
		if (!get_environ()->pid && (get_environ()->pid = fork()) > 0
			&& (get_environ()->pgid = get_environ()->pid))
			return (0);
		else if (get_environ()->pid < 0)
			return (write(2, "42sh: fork error\n", 17));
		if (bg != -1)
			ft_set_sh_signal(bg ? S_CHLD : S_CHLD_FG);
		get_environ()->setvar ? ft_set_var(get_environ()->setvar, ENVAR) : 0;
		execve(path, cmd, get_environ()->envar);
		if ((fd = open(path, O_RDONLY)) >= 0)
			exit(main_loop(fd));
		exit(ft_dprintf(2, "%s: permission denied\n", *cmd) ? -2 : 0);
	}
	if (access(path, F_OK)
		&& ft_dprintf(2, "%s: No such file or directory\n", *cmd))
		return (127);
	S_ISDIR(tmp.st_mode) ? ft_dprintf(2, "%s: is a directory\n", *cmd)
		: ft_dprintf(2, "%s: permission denied\n", *cmd);
	return (126);
}

static char	**ft_get_path(const char *altpath)
{
	char	pwd[MAXPATHLEN];
	t_list	*list;

	if (!altpath)
	{
		if ((list = get_environ()->setvar))
		{
			while (list)
			{
				if (ft_strcmp((char *)list->content, "PATH") == '=')
				{
					altpath = ft_strchr((char *)list->content, '=') + 1;
					break ;
				}
				list = list->next;
			}
		}
		else
			altpath = ft_getenv("PATH");
		if (!altpath || !*altpath)
			altpath = getcwd(pwd, MAXPATHLEN);
	}
	return (ft_strsplit(altpath, ':'));
}

char		*ft_search_bin(char *bin_name, const char *altpath)
{
	int		i;
	char	*exec_path;
	char	**path;

	i = 0;
	exec_path = NULL;
	if (!(path = ft_get_path(altpath)))
		return (NULL);
	while (path[i])
	{
		if (!(exec_path = malloc(ft_strlen(path[i]) + ft_strlen(bin_name) + 2)))
			return (NULL);
		ft_strcpy(exec_path, path[i]);
		ft_strcat(ft_strcat(exec_path, "/"), bin_name);
		if (!access(exec_path, F_OK))
			break ;
		ft_memdel((void**)&exec_path);
		free(path[i++]);
	}
	while (path[i])
		free(path[i++]);
	free(path);
	return (exec_path);
}

int			ft_argv_exec(char **cmd, char *altpath, int bg)
{
	char	*bin_path;
	int		st;

	if (!cmd || !*cmd)
	{
		return (get_environ()->setvar
				? ft_set_var(get_environ()->setvar, SHVAR) : 0);
	}
	bin_path = NULL;
	if (ft_strchr(*cmd, '/'))
		st = ft_exec_bypath(cmd, *cmd, bg);
	else if ((st = ft_exec_builtin(cmd)) == -1)
	{
		if ((bin_path = ft_search_bin(*cmd, altpath)))
			st = ft_exec_bypath(cmd, bin_path, bg);
		else if ((st = 127))
			ft_dprintf(2, "%s: command not found\n", *cmd);
	}
	free(bin_path);
	return (st);
}
