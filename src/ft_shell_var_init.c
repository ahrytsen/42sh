/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_var_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 13:23:36 by dlinkin           #+#    #+#             */
/*   Updated: 2018/09/02 13:23:37 by dlinkin          ###   ########.fr       */
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
