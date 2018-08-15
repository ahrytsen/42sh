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

int		ft_is_valid_name(char *str)
{
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void		ft_var_checker(t_list *lst)
{
	t_token	*tmp;
	char	*str;

	if (get_environ()->setvar)
		ft_lstfree(&get_environ()->setvar);
	while (lst)
	{
		tmp = lst->content;
		if (tmp->type == (enum e_ast_type)word)
		{
			if ((str = ft_strchr(tmp->data.word, '='))
			&& ft_is_valid_name(tmp->data.word))
			{
				ft_lstpush_back(&get_environ()->setvar, tmp->data.word
				, ft_strlen(tmp->data.word) + 1);
				tmp->type = (enum e_ast_type)assignment;
			}
			else
				break ;
		}
		lst = lst->next;
	}
}

t_env		*get_environ(void)
{
	static t_env	env;

	return (&env);
}

char		*ft_getenv(const char *name)
{
	t_var	*entry;
	char	*ptr;

	if (!name || !(entry = ft_get_shvar_entry(name)))
		return (NULL);
	ptr = ft_strchr(entry->var, '=') + 1;
	return (ptr);
}

char		*ft_other_getenv(const char *name)
{
	char	**env;

	env = get_environ()->envar;
	if (!name || !env)
		return (NULL);
	while (*env)
	{
		if (ft_strcmp(*env, name) == '=')
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}

int		ft_set_var(t_list *var, int mod)
{
	char	*value;
	char	*ptr;
	t_var	*entry;

	while (var)
	{
		ptr = ft_strchr(var->content, '=');
		value = ptr + 1;
		*ptr = '\0';
		if (mod == SHVAR)
		{
			if ((entry = ft_get_shvar_entry(var->content)))
			{
				if (entry->attr == 'e')
					ft_setter(var->content, value, 1);
				free(entry->var);
				*ptr = '=';
				entry->var = ft_strdup(var->content);
			}
			else
				ft_set_tool(var->content, value, 1, SHVAR);
		}
		else if (mod == ENVAR)
			ft_setter(var->content, value, 1);
		var = var->next;
	}
	return (0);
}
