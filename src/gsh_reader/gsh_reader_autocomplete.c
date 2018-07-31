/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_autocomplete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:32:41 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/29 18:32:43 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void		search_in_path(t_list **list, char *str, int i, size_t len)
{
	char			*path;
	char			part[NAMESIZE];
	DIR				*directory;
	struct dirent	*fl;

	path = gsh_get_env("PATH");
	while ((i = gsh_get_path_name(part, path, "")))
	{
		if ((directory = opendir(part)))
		{
			while ((fl = readdir(directory)))
			{
				if (fl->d_name[0] != '.' && !ft_strncmp(str, fl->d_name, len))
					ft_lstpushback(list, ft_lstnew((void *)fl->d_name
					, ft_strlen(fl->d_name) + 1));
			}
			closedir(directory);
		}
		path += i;
		if (*path)
			path++;
	}
}

static void		gogo_commandname(char *str, size_t len, t_pos *pos, char *out)
{
	t_list				*list;
	extern const t_fptr	g_builtin[8];
	int					i;

	i = 0;
	list = NULL;
	while (g_builtin[i].name)
	{
		if (!ft_strncmp(str, g_builtin[i].name, len))
			ft_lstpushback(&list, ft_lstnew((void *)g_builtin[i].name
				, ft_strlen(g_builtin[i].name) + 1));
		i++;
	}
	search_in_path(&list, str, 0, len);
	reprint(ft_lstsort(list), out, pos, len);
}

static void		gogo_envarname(char *str, size_t len, t_pos *pos, char *out)
{
	t_list	*list;
	char	**env;
	char	*in;
	int		i;

	list = NULL;
	env = gsh_bucket(RETURN_ENV, 0);
	i = -1;
	while (env && env[++i])
		if (!ft_strncmp(str, env[i], len))
		{
			in = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			ft_lstpushback(&list, ft_lstnew((void *)in, ft_strlen(in) + 1));
			free(in);
		}
	env = gsh_bucket(RETURN_SH, 0);
	i = -1;
	while (env && env[++i])
		if (!ft_strncmp(str, env[i], len))
		{
			in = ft_strsub(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			ft_lstpushback(&list, ft_lstnew((void *)in, ft_strlen(in) + 1));
			free(in);
		}
	reprint(ft_lstsort(list), out, pos, len);
}

static int		zeroed(char *out, size_t len)
{
	while (len && (out[len - 1] == ' ' || out[len - 1] == '\t')
		&& out[len - 1] != ';' && out[len - 1] != '|' && out[len - 1] != '&')
		len--;
	if (!len || out[len - 1] == ';' || out[len - 1] == '|'
		|| out[len - 1] == '&')
		return (1);
	return (0);
}

void			gsh_r_autocomplete(char *out, t_pos *pos)
{
	size_t			len;
	char			s[LINE_SIZE];
	extern uint32_t	g_opt_n;

	len = pos->kur;
	while (len && out[len - 1] != ' ' && out[len - 1] != '\t' && out[len] != '$'
		&& out[len - 1] != ';' && out[len - 1] != '|' && out[len - 1] != '&')
		len--;
	while (pos->kur < pos->len && out[pos->kur] != ' ' && out[pos->kur] != '\t'
	&& out[pos->kur] != ';' && out[pos->kur] != '|' && out[pos->kur] != '&')
		gsh_r_shift_right(pos);
	ft_strncpy(s, out + len, pos->kur - len);
	s[pos->kur - len] = 0;
	if (!(g_opt_n & COMPL_EMPTY) && ft_is_blank(s))
	{
		write(0, "\a", 1);
		return ;
	}
	if (zeroed(out, len) && *s != '~' && *s != '$' && *s != '.' && *s != '/'
		&& *s != '!')
		gogo_commandname(s, pos->kur - len, pos, out);
	else if (*s == '$')
		gogo_envarname(s + 1, pos->kur - len - 1, pos, out);
	else
		gogo_filename(s, pos->kur - len, pos, out);
}
