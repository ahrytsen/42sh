/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_var_toolz.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:28:03 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/10 18:28:05 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static t_var	*ft_new_shvar_entry(char *entry, char attr)
{
	t_var	*new;

	if (!(new = (t_var *)ft_memalloc(sizeof(t_var))))
		return (NULL);
	if (!(new->var = ft_strdup(entry)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->attr = attr;
	return (new);
}

void			ft_add_shvar_entry(char *entry, char attr)
{
	t_var	*iter;
	t_var	*new;
	t_var	*ptr;

	if (!(new = ft_new_shvar_entry(entry, attr)))
		return ;
	if (!(iter = get_environ()->shvar))
	{
		get_environ()->shvar = new;
		return ;
	}
	ptr = NULL;
	while (iter)
	{
		if (ft_strcmp(iter->var, new->var) > 0)
		{
			ptr ? ptr->next = new : 0;
			new->next = iter;
			break ;
		}
		ptr = iter;
		iter = iter->next;
	}
	!iter ? ptr->next = new : 0;
	!ptr ? get_environ()->shvar = new : 0;
}

t_var			*ft_get_shvar_entry(const char *name)
{
	t_var	*iter;

	if ((iter = get_environ()->shvar))
	{
		while (iter)
		{
			if (ft_strcmp(iter->var, name) == '='
			|| !ft_strcmp(iter->var, name))
				return (iter);
			iter = iter->next;
		}
	}
	return (NULL);
}

int				ft_rem_shvar_entry(const char *name)
{
	t_var	*iter;
	t_var	*tmp;

	tmp = NULL;
	if ((iter = get_environ()->shvar))
	{
		while (iter)
		{
			if (!ft_strncmp(iter->var, name, ft_strlen(name)))
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

int				ft_print_shvar(int mod)
{
	t_var *env;

	env = get_environ()->shvar;
	while (env)
	{
		if (mod & 1 && env->attr == 'l')
			ft_printf("%s\n", env->var);
		else if (mod & 2)
			ft_printf("%c %s\n", env->attr, env->var);
		else if ((!mod || mod & 4) && (env->attr == 'e' || env->attr == 'u'))
			ft_printf("export %s\n", env->var);
		env = env->next;
	}
	return (0);
}
