/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_read_records.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 13:53:16 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/03 17:25:09 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	check_ifs_val(char *ifs)
{
	return (!ifs || (ft_strlen(ifs) == 3 &&
					ft_strchr(ifs, ' ') &&
					ft_strchr(ifs, '\n') &&
					ft_strchr(ifs, '\t')));
}

char		*skip_ifs_delim(char *s, char *ifs)
{
	char	nonspace;

	if (s)
	{
		nonspace = 0;
		while (*s && ft_strchr(ifs, *s))
		{
			if (!ft_iswhitespace(*s))
			{
				if (!nonspace)
					nonspace = 1;
				else
					break ;
			}
			++s;
		}
	}
	return (s);
}

static int	check_newline(char *s)
{
	if (s && s[ft_strlen(s) - 1] == '\\')
		while (*s)
		{
			if (*s == '\\' && !*(s + 1))
			{
				*s = 0;
				return (1);
			}
			++s;
		}
	return (0);
}

void		record_vals(char **av, char *s, char r_flag)
{
	char	buf[s ? ft_strlen(s) + 1 : 1];
	int		i;
	char	*ifs;

	i = 0;
	ft_bzero(buf, sizeof(buf));
	if (!(ifs = ft_getenv("IFS")))
		ifs = " \t\n";
	while (*av)
	{
		if (!*(av + 1))
		{
			ft_set_tool(*av, s, 1, SHVAR);
			break ;
		}
		while (s && !ft_strchr(ifs, *s))
			if (*s == '\\' && !r_flag)
				s += 2;
			else
				buf[i++] = *s++;
		ft_set_tool(*av++, buf, 1, SHVAR);
		ft_bzero(buf, i);
		i = 0;
		s = skip_ifs_delim(s, ifs);
	}
}

void		read_line(char **av, char r_flag)
{
	char	*s;
	char	*tmp_s;

	s = NULL;
	tmp_s = NULL;
	while (1)
	{
		if (get_next_line(1, &tmp_s) == -1)
		{
			free(s);
			return ;
		}
		s = s ? ft_strextend(s, tmp_s) : tmp_s;
		if (!r_flag && check_newline(s))
			continue ;
		break ;
	}
	if (check_ifs_val(ft_getenv("IFS")))
	{
		tmp_s = s;
		s = ft_strtrim(s);
		free(tmp_s);
	}
	record_vals(*av ? av : (char *[]){"REPLY", NULL}, s, r_flag);
	free(s);
}
