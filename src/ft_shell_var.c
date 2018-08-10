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

void	ft_init_shell_var(void)
{
	char	*str;
	char	*ptr;
	char	**env;

	get_environ()->shvar = NULL;
	if ((env = get_environ()->envar))
		while (*env)
		{
			ft_add_shvar_entry(*env, 'e');
			env++;
		}
	ft_add_shvar_entry("?=0", 'l');
	str = ft_itoa(getpid());
	ptr = ft_strjoin("$=", str);
	ft_add_shvar_entry(ptr, 'l');
	free(str);
	free(ptr);
	str = ft_strjoin(getpwuid(getuid())->pw_dir, "/.ft_history");
	ptr = ft_strjoin("HISTFILE=", str);
	ft_add_shvar_entry(ptr, 'l');
	free(str);
	free(ptr);
	ft_add_shvar_entry("HISTSIZE=42", 'l');
	ft_add_shvar_entry("HISTFILESIZE=42", 'l');
}

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

t_env		*get_environ(void)
{
	static t_env	env;

	return (&env);
}

char		*ft_getenv(const char *name)
{
	// char	**env;
    //
	// if (!name || !(env = get_environ()->envar))
	// 	return (NULL);
	// while (*env)
	// {
	// 	if (ft_strcmp(*env, name) == '=')
	// 		return (ft_strchr(*env, '=') + 1);
	// 	env++;
	// }
	// return (NULL);

	t_var	*entry;
	char	*ptr;

	if (!name || !(entry = ft_get_shvar_entry(name)))
		return (NULL);
	ptr = ft_strchr(entry->var, '=') + 1;
	return (ptr);
}

int		ft_set_shell_var(char **cmd)
{
	char	*value;
	char	*ptr;
	t_var	*entry;

	while (*cmd)
	{
		ptr = ft_strchr(*cmd, '=');
		value = ptr + 1;
		*ptr = '\0';
		if ((entry = ft_get_shvar_entry(*cmd)))
		{
			if (entry->attr == 'e')
				ft_setter(*cmd, value, 1);
			free(entry->var);
			*ptr = '=';
			entry->var = ft_strdup(*cmd);
		}
		else
			ft_set_tool(*cmd, value, 1, SHVAR);
		cmd++;
	}
	return (0);
}
