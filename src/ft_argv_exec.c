/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:27:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:21:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_exec_builtin(char **cmd)
{
	int						i;
	const static t_builtins	builtins[] = {
		{"echo", &ft_echo},
		{"cd", &ft_cd},
		{"fg", &ft_fg},
		{"setenv", &ft_setenv_builtin},
		{"unsetenv", &ft_unsetenv_builtin},
		{"env", &ft_env},
		{"exit", &ft_exit},
		{NULL, NULL}
	};

	i = 0;
	while (builtins[i].cmd && ft_strcmp(cmd[0], builtins[i].cmd))
		i++;
	return (builtins[i].cmd ? builtins[i].ft_builtin(cmd + 1) : -1);
}

static int	ft_exec_bypath(char **cmd, char *path, int bg)
{
	struct stat	tmp;

	if (path && !access(path, F_OK) && !access(path, X_OK)
		&& !stat(path, &tmp) && S_ISREG(tmp.st_mode))
	{
		if (!get_environ()->pid && (get_environ()->pid = fork()) > 0
			&& (get_environ()->pgid = get_environ()->pid))
			return (0);
		else if (get_environ()->pid < 0)
			return (ft_dprintf(2, "21sh: fork error\n"));
		if (bg != -1 && get_environ()->is_interactive)
			ft_set_sh_signal(bg ? S_CHLD : S_CHLD_FG);
		execve(path, cmd, get_environ()->env);
		if (dup2(open(path, O_RDONLY), 0) != -1)
			return (main());
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

	if (!altpath)
	{
		altpath = ft_getenv("PATH");
		if (!altpath || !*altpath)
			altpath = getcwd(pwd, MAXPATHLEN);
	}
	return (ft_strsplit(altpath, ':'));
}

static char	*ft_search_bin(char *bin_name, const char *altpath)
{
	int				i;
	char			*exec_path;
	char			**path;

	i = 0;
	exec_path = NULL;
	if (!(path = ft_get_path(altpath)))
		return (NULL);
	while (path[i])
	{
		if (!(exec_path = malloc(ft_strlen(path[i]) + ft_strlen(bin_name) + 2)))
			return (NULL);
		ft_strcpy(exec_path, path[i]);
		ft_strcat(exec_path, "/");
		ft_strcat(exec_path, bin_name);
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

	bin_path = NULL;
	if (!cmd || !*cmd)
		return (0);
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
