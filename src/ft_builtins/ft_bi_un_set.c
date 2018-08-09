/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_un_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 13:31:36 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/08 13:32:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/* ************************************************************************** */

static void	inner_loop(t_var **head, int *mark, int count)
{
	t_var	*list;
	int		j;
	char	*var;
	char	attr;

	j = 0;
	list = *head;
	while (j < count)
	{
		if (ft_strcmp((char *)list->var, (char *)list->next->var) > 0)
		{
			*mark = 1;
			var = list->var;
			attr = list->attr;
			list->var = list->next->var;
			list->attr = list->next->attr;
			list->next->var = var;
			list->next->attr = attr;
		}
		list = list->next;
		j++;
	}
}

t_var		*ft_sort_entry(t_var *alst)
{
	int		i;
	int		num;
	int		mark;
	t_var	*tmp;

	if (!alst)
		return (NULL);
	tmp = alst;
	num = 0;
	while (tmp)
	{
		tmp = tmp->next;
		num++;
	}
	i = 1;
	while (i < num)
	{
		mark = 0;
		inner_loop(&alst, &mark, num - i);
		if (!mark)
			break ;
		i++;
	}
	return (alst);
}

/* ************************************************************************** */

int		ft_unset(char **av)
{
	int	ret;

	ret = 0;
	if (!av)
		return (256);
	while (*av)
		if (ft_unset_tool(*av++, SHVAR))
			ret = 256;
	return (ret);
}

int			ft_print_shvar(void)
{
	t_var *env;

	env = ft_sort_entry(get_environ()->shvar);
	while (env)
	{
		ft_printf("%s\n", env->var);
		env = env->next;
	}
	return (0);
}

int		ft_set(char **av)
{
	// char	*value;
	// int		i;
	int		ret;

	ret = 0;
	if (!av)
		return (256);
	if (!*av)
		ft_print_shvar();
	// while (*av)
	// {
	// 	if ((value = ft_strchr(*av, '=')))
	// 		*value++ = '\0';
	// 	i = -1;
	// 	while ((*av)[++i])
	// 		if (((i && !ft_isalnum((*av)[i])) || (!i && !ft_isalpha((*av)[i])))
	// 		&& (*av)[i] != '_'
	// 		&& ft_dprintf(2, "set: `%s': not a valid identifier\n", *av + 1))
	// 			return (256);
	// 	if (ft_set_tool(*av++, value, 1, SHVAR))
	// 		ret = 256;
	// }
	return (ret);
}
