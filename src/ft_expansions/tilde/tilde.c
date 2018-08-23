/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 02:34:57 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/23 08:08:11 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

static char	*normalnyy_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcat(str, s1);
	ft_strcat(str, s2);
	return (str);
}

static char	*get_user_homedir(char *s)
{
	char			*tmp;
	struct passwd	*pwd;

	tmp = s;
	while ((*s != ':' && *s != '/') && *s)
		++s;
	tmp = ft_strsub(tmp, 0, s - tmp);
	pwd = getpwnam(tmp);
	free(tmp);
	return (pwd ? ft_strjoin(pwd->pw_dir, s) : NULL);
}

static char	*get_curr_user(char *s)
{
	char	*tmp;

	if (!(tmp = ft_other_getenv("HOME")))
			tmp = getpwuid(getuid())->pw_dir;
	return (normalnyy_strjoin(tmp, s));
}

void	expand_tilde(t_list *lst)
{
	char	*s;

	s = lst->content;
	if (*s != '~')
		return ;
	++s;
	if (*s == '/' || !*s)
		s = get_curr_user(s);
	else if (*s == '-' && ft_strchr("/:", *(s + 1)))
		s = normalnyy_strjoin(ft_other_getenv("OLDPWD"), s + 1);
	else if (*s == '+' && ft_strchr("/:", *(s + 1)))
		s = normalnyy_strjoin(ft_other_getenv("PWD"), s + 1);
	else
		s = get_user_homedir(s);
	if (s)
	{
		free(lst->content);
		lst->content = s;
	}
}