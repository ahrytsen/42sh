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
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((!i && !ft_isalpha(str[i]) && str[i] != '_')
		|| (i && !ft_isalnum(str[i]) && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_var_checker(t_list *lst)
{
	t_token	*tmp;

	if (get_environ()->setvar)
		ft_lstfree(&get_environ()->setvar);
	while (lst)
	{
		tmp = lst->content;
		if (tmp->type == (enum e_ast_type)word)
		{
			if (ft_strchr(tmp->data.word, '=')
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

t_env	*get_environ(void)
{
	static t_env	env;

	return (&env);
}

char	*ft_getenv(const char *name)
{
	t_var	*entry;
	char	*ptr;

	if (!name || !(entry = ft_get_shvar_entry(name)))
		return (NULL);
	if ((ptr = ft_strchr(entry->var, '=')))
		return (ptr + 1);
	return (ptr);
}

char	*ft_other_getenv(const char *name)
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
