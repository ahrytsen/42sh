/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 08:17:22 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/02 14:36:41 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_expansions.h"

static void	handler_func(int i)
{
	(void)i;
}

static void	handle_sigint(void)
{
	struct sigaction	int_handler;

	ft_bzero(&int_handler, sizeof(struct sigaction));
	int_handler.sa_handler = handler_func;
	sigaction(SIGINT, &int_handler, 0);
	//	ft_printf("%i\n",siginterrupt(SIGINT, 1));
}

static char	**check_flags(char **av, char *r_flag)
{
	char	*s;

	if (av)
		while(*av && **av == '-')
		{
			if (ft_strequ(*av, "--"))
				return (av + 1);
			s = *av;
			while (*++s)
				if (*s != 'r')
				{
					ft_dprintf(2, "42sh: read: %s: invalid option\n"
								"read: usage: read [-r] [name ...]\n");
					return (NULL);
				}
				else
					*r_flag = 1;
			++av;
		}
	return (av);
}

static int	check_var_names(char **av)
{
	(void)av;
//	char	*s;
//
//	if (av)
//		while (*av)
//		{
//			s = *av;
//			while (*s)
//				if (!ft_isword(*s))
//				{
//					ft_dprintf(2,
//							"42sh: read: %s: not a valid identifier\n", *av);
//					return (0);
//				}
//			++av;
//		}
	return (1);
}

static int	check_ifs_val(char *ifs)
{
	return (!ifs || (ft_strlen(ifs) == 3 &&
			ft_strchr(ifs, ' ') &&
			ft_strchr(ifs, '\n') &&
			ft_strchr(ifs, '\t')));
}

char			*skip_ifs_delim(char *s, char *ifs)
{
	char	nonspace;

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
	return (s);
}

void	record_vals(char **av, char *s, char r_flag)
{
	char	buf[ft_strlen(s) + 1];
	int		i;
	char	*ifs;

	i = 0;
	ifs = ft_getenv("IFS");
	if (!ifs)
		ifs = " \t\n";
//	ft_printf("IFS: %s\n", ifs);
	ft_bzero(buf, sizeof(buf));
	while (*av)
	{
		while (!ft_strchr(ifs, *s))
		{
			if (*s == '\\' && !r_flag)
				++s;
			buf[i++] = *s++;
		}
		ft_set_tool(*av++, buf, 1, SHVAR);
		ft_bzero(buf, i);
		i = 0;
		s = skip_ifs_delim(s, ifs);
		if (!*(av + 1))
		{
			ft_set_tool(*av, s, 1, SHVAR);
			break ;
		}
	}
}

static int	check_newline(char *s)
{
	if (s)
		while (*s)
		{
			if (*s == '\\' && !*++s)
			{
				*s = 0;
				return (1);
			}
			++s;
		}
	return (0);
}

static int	read_line(char **av, char r_flag)
{
	char	*s;
	char	*tmp_s;

	s = NULL;
	while (1)
	{
		if (get_next_line(1, &tmp_s) == -1)
			return (1);
		s = s ? ft_strextend(s, tmp_s) : tmp_s;
		if (check_newline(s) && !r_flag)
			continue ;
		break ;
	}
	if (check_ifs_val(ft_getenv("IFS")))
	{
		tmp_s = s;
		s = ft_strtrim(s);
		free(tmp_s);
	}
	record_vals(av, s, r_flag);
	free(s);
	return (0);
}

int			ft_bi_read(char **av)
{
	char	r_flag;

	r_flag = 0;
	handle_sigint();
	if (!(av = check_flags(av, &r_flag)) ||
			!check_var_names(av) ||
			read_line(av, r_flag))
		return (256);
	signal(SIGINT, SIG_IGN);
	return (0);
}
