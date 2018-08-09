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

void	ft_add_shvar_entry(char *entry, char attr)
{
	t_var	*tmp;
	t_var	*new;

	tmp = get_environ()->shvar;
	if (!(new = (t_var *)ft_memalloc(sizeof(t_var))))
		return ;
	if (!(new->var = ft_strdup(entry)))
	{
		free(new);
		return ;
	}
	new->next = NULL;
	new->attr = attr;
	if (!tmp)
	{
		get_environ()->shvar = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_var		*ft_get_shvar_entry(char *name)
{
	t_var	*iter;

	if ((iter = get_environ()->shvar))
	{
		while (iter)
		{
			if (ft_strcmp(iter->var, name) == '=')
				return (iter);
			iter = iter->next;
		}
	}
	return (NULL);
}

int		ft_rem_shvar_entry(const char *name)
{
	t_var	*iter;
	t_var	*tmp;

	tmp = NULL;
	if ((iter = get_environ()->shvar))
	{
		while (iter)
		{
			if (ft_strcmp(iter->var, name) == '=')
			{
				if (tmp)
				 	tmp->next = iter->next;
				tmp = iter;
				free(tmp->var);
				free(tmp);
				return (1);
			}
			tmp = iter;
			iter = iter->next;
		}
		if (!tmp)
			get_environ()->shvar = iter;
	}
	return (0);
}


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
	ft_add_shvar_entry("?=0", 0);
	str = ft_itoa(getpid());
	ptr = ft_strjoin("$=", str);
	ft_add_shvar_entry(ptr, 0);
	free(str);
	free(ptr);
	str = ft_strjoin(getpwuid(getuid())->pw_dir, "/.ft_history");
	ptr = ft_strjoin("HISTFILE=", str);
	ft_add_shvar_entry(ptr, 0);
	free(str);
	free(ptr);
	ft_add_shvar_entry("HISTSIZE=42", 0);
	ft_add_shvar_entry("HISTFILESIZE=42", 0);
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

int		ft_set_shell_var(char **cmd)
{

	while (*cmd)
	{

		cmd++;
	}
	return (0);
}
