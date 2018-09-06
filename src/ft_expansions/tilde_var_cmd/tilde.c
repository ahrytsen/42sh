/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 02:34:57 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/05 18:14:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"
#include "ft_sh.h"

static void	get_user_homedir(t_buf **buf, char **s)
{
	char			*tmp;
	struct passwd	*pwd;

	tmp = *s;
	while (**s != ':' && **s != '/' && **s)
		if (**s == '\\')
			*++(*s) ? (*s)++ : 0;
		else if (ft_strchr("'\"", **s))
			ft_skip_quotes(s);
		else
			++(*s);
	tmp = ft_strsub(tmp, 0, *s - tmp);
	pwd = getpwnam(tmp);
	if (pwd)
		ft_putstrq_mshbuf(buf, pwd->pw_dir, -1, "'\"\\");
	else
	{
		ft_putchar_mshbuf(buf, '~');
		ft_putstr_mshbuf(buf, tmp, -1);
	}
	free(tmp);
}

static void	get_curr_user(t_buf **buf)
{
	char	*tmp;

	if (!(tmp = ft_other_getenv("HOME")))
		tmp = getpwuid(getuid())->pw_dir;
	ft_putstrq_mshbuf(buf, tmp, -1, "'\"\\");
}

void		expand_tilde(t_buf **buf, char **s)
{
	if (!s || !*s || **s != '~')
		return ;
	++(*s);
	if (ft_strchr("/:", **s))
		get_curr_user(buf);
	else if (**s == '-' && ft_strchr("/:", *(*s + 1)) && (*s)++)
		ft_putstrq_mshbuf(buf, ft_other_getenv("OLDPWD"), -1, "'\"\\");
	else if (**s == '+' && ft_strchr("/:", *(*s + 1)) && (*s)++)
		ft_putstrq_mshbuf(buf, ft_other_getenv("PWD"), -1, "'\"\\");
	else
		get_user_homedir(buf, s);
}
