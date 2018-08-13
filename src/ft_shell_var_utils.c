/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_var_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:44:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:20:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	*ft_new_env_str(const char *name, const char *value)
{
	char	*new_env;
	size_t	name_l;
	size_t	value_l;

	if (!name)
		return (NULL);
	name_l = ft_strlen(name);
	value_l = (value ? ft_strlen(value) : 0);
	if (!(new_env = (char*)malloc(sizeof(char) * (name_l + value_l + 2))))
		return (NULL);
	ft_strcpy(new_env, name);
	new_env[name_l] = '=';
	ft_strcpy(new_env + name_l + 1, value ? value : "");
	return (new_env);
}

int			ft_setter(const char *name, const char *value, int overwrite)
{
	size_t	i;
	char	**env;
	char	*tmp;

	if (!(env = get_environ()->envar)
		|| !(tmp = ft_new_env_str(name, value)))
		return (-1);
	i = -1;
	while (env[++i])
		if (ft_strcmp(env[i], name) == '=')
		{
			if (!overwrite)
			{
				free(tmp);
				return (-1);
			}
			free((void*)env[i]);
			return ((env[i] = tmp) ? 0 : -1);
		}
	if (!(env = ft_memalloc(sizeof(char*) * (i + 2))))
		return (-1);
	ft_memcpy(env, get_environ()->envar, sizeof(char*) * i);
	env[i] = tmp;
	free(get_environ()->envar);
	return ((get_environ()->envar = env) ? 0 : -1);
}

int			ft_set_tool(const char *name, const char *value, int overwrite
	, int mod)
{
	char	*str;
	t_var	*entry;
	int		rat;

	rat = 0;
	if (((entry = ft_get_shvar_entry(name)) && !overwrite)
	|| !(str = ft_new_env_str(name, value)))
		return (-1);
	if (mod == SHVAR)
	{
		ft_add_shvar_entry(str, ((entry && entry->attr == 'e') ? 'e' : 'l'));
		if (entry && entry->attr == 'e'
		&& (rat = ft_setter(name, value, overwrite)) == -1)
			ft_rem_shvar_entry(name);
	}
	else
	{
		if (entry)
		{
			entry->attr = 'e';
			free(entry->var);
			entry->var = ft_strdup(str);
		}
		else
			ft_add_shvar_entry(str, 'e');
		if ((rat = ft_setter(name, value, overwrite)) == -1)
			ft_rem_shvar_entry(name);
	}
	free(str);
	return (rat);
}

int			ft_unset_tool(const char *name, int mod)
{
	char	**env;
	char	attr;
	t_var	*entry;

	if (!(entry = ft_get_shvar_entry(name))
	|| ((attr = entry->attr) != 'e' && mod == ENVAR))
		return (0);											// | -1?
	if (!ft_rem_shvar_entry(name))
		return (-1);
	if (attr != 'e')
		return (0);
	env = get_environ()->envar;
	if (!env || !name || ft_strchr(name, '='))
		return (-1);
	while (*env && ft_strcmp(*env, name) != '=')
		env++;
	if (!*env)
		return (-1);
	free(*env);
	while (*env++)
		*(env - 1) = *env;
	return (0);
}
