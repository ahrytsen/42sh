/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 14:21:11 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/08 14:21:12 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_var_checker(char ***cmd)
{
	char	*str;
	char	*ptr;
	char	**tmp;

	tmp = *cmd;
	while (**cmd)
	{
		if (!(str = ft_strchr(**cmd, '=')))
			return (0);
		if ((ptr = ft_strchr(**cmd, '/')) && str > ptr)
			return (0);
		(*cmd)++;
	}
	*cmd = tmp;
	return (1);
}

int		ft_set_shell_var(char **cmd)
{
	while (*cmd)
	{

		cmd++;
	}
	return (0);
}

void	ft_init_shell_var(void)
{
	char	*str;
	char	**shvar;

	if (!(get_environ()->shvar = ft_memalloc(sizeof(char*) * 1)))
		return (NULL);
	ft_set_tool("?", "0", 1, SHVAR);
	str = ft_itoa(getpid());
	ft_set_tool("$", str, 0, SHVAR);
	free(str);
	str = ft_strjoin(getpwuid(getuid())->pw_dir, "/.ft_history");
	ft_set_tool("HISTFILE=", str, 0, SHVAR);
	free(str);
	ft_set_tool("HISTSIZE", "42", 0, SHVAR);
	ft_set_tool("HISTFILESIZE", "42", 0, SHVAR);
}
