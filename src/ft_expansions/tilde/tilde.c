/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 02:34:57 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/23 05:28:08 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

char	*get_user_homedir(char *s)
{
	char			*tmp;
	struct passwd	*pwd;

	tmp = s;
	while (*s != '/' && *s)
		++s;
	tmp = ft_strsub(tmp, 0, tmp - s);
	pwd = getpwnam(tmp);
	free(tmp);
	return (pwd ? ft_strjoin(pwd->pw_dir, s) : NULL);
}

char	*get_curr_user(char *s)
{
	char	*tmp;

	if (!(tmp = ft_getenv("HOME")))
			tmp = getpwuid(getuid())->pw_dir;
	return (ft_strjoin(tmp, s));
}

int 	main(int ac, char **av)
{
	char	*s;

	s = av[1] ? av[1] : "~\0";
	if (*s != '~')
		return (0);
	++s;
	if (*s == '/' || !*s)
		s = get_curr_user(s + 1);
	else if (*s == '-')
		s = ft_strjoin(ft_getenv("OLDPWD"), s + 1);
	else if (*s == '+')
		s = ft_strjoin(ft_getenv("PWD"), s + 1);
	else
		s = get_user_homedir(s);
	ft_printf("%s\n", s);
	return (0);
}