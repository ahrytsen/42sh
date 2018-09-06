/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_read_records.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 13:53:16 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/06 14:45:35 by ahrytsen         ###   ########.fr       */
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

static char	*skip_ifs_delim(char *s, char *ifs)
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

static void	record_vals(char **av, char *s, char r_flag)
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
			ft_set_tool(*av, r_flag ? s : get_last_var(s, buf, &i), 1, SHVAR);
			break ;
		}
		while (s && !ft_strchr(ifs, *s))
			if (*s == '\\' && !r_flag && *++s)
				*s != '\n' ? (buf[i++] = *s++) : (int)s++;
			else if (*s)
				buf[i++] = *s++;
		ft_set_tool(*av++, buf, 1, SHVAR);
		ft_bzero(buf, i);
		i = 0;
		s = skip_ifs_delim(s, ifs);
	}
}

static int	get_line(char **line, char r_flag)
{
	t_buf	*head;
	t_buf	*cur;
	char	buf;
	char	quot;
	int		rd;

	quot = 0;
	line ? (*line = NULL) : 0;
	if (!line || !(head = ft_memalloc(sizeof(t_buf))))
		return (-1);
	cur = head;
	while ((rd = read(0, &buf, 1)) > 0)
	{
		if (!r_flag && !quot && buf == '\\')
			quot = 1;
		else if ((r_flag || !quot) && buf == '\n')
			break ;
		else
			quot = 0;
		ft_putchar_mshbuf(&cur, buf);
	}
	*line = (rd < 0 ? ft_free_mshbuf(head) : ft_buftostr(head));
	return (rd < 0 ? 1 : 0);
}

void		read_line(char **av, char r_flag)
{
	char	*s;
	char	*tmp_s;

	s = NULL;
	tmp_s = NULL;
	if (get_line(&s, r_flag))
		return ;
	if (check_ifs_val(ft_getenv("IFS")))
	{
		tmp_s = s;
		s = ft_strtrim(s);
		free(tmp_s);
	}
	record_vals(av && *av ? av : (char *[]){"REPLY", NULL}, s, r_flag);
	free(s);
}
