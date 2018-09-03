/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 14:21:11 by dlinkin           #+#    #+#             */
/*   Updated: 2018/09/02 18:56:40 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_expansions.h"

int			ft_is_valid_name(char *str)
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

static char	*ft_assign_expansions(char *str)
{
	char	*value;
	char	*sign;
	char	*res;
	t_list	tmp;

	if (!(sign = ft_strchr(str, '=')))
		return (str);
	value = ft_strdup(sign + 1);
	sign[1] = '\0';
	ft_bzero(&tmp, sizeof(t_list));
	tmp.content = value;
	ft_lstiter(&tmp, substitute_variable);
	ft_lstiter(&tmp, remove_quotes);
	res = ft_strjoin(str, tmp.content);
	free(tmp.content);
	free(str);
	return (res);
}

void		ft_var_checker(t_list *lst)
{
	char	*assign;
	t_token	*tmp;

	if (get_environ()->setvar)
		ft_lstfree(&get_environ()->setvar);
	while (lst)
	{
		tmp = lst->content;
		if (tmp->type == word || tmp->type == assignment)
		{
			if (tmp->type == assignment
				|| (ft_strchr(tmp->word, '=') && ft_is_valid_name(tmp->word)))
			{
				if ((assign = ft_assign_expansions(ft_strdup(tmp->word))))
					ft_lstpush_back(&get_environ()->setvar, assign,
										ft_strlen(assign) + 1);
				free(assign);
				tmp->type = assignment;
			}
			else
				break ;
		}
		lst = lst->next;
	}
}

char		*ft_getenv(const char *name)
{
	t_var	*entry;
	char	*ptr;

	if (!name || !(entry = ft_get_shvar_entry(name)))
		return (NULL);
	if ((ptr = ft_strchr(entry->var, '=')))
		return (ptr + 1);
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
