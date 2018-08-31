/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bslash_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 04:53:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/31 04:56:15 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expansions.h"

static void	record_hex(t_buf **cur, char **line)
{
	int		i;
	char	buf[3];

	++*line;
	i = 0;
	ft_bzero(buf, 3);
	while (ft_isxdigit(**line) && i < 2)
		buf[i++] = *(*line)++;
	ft_putchar_mshbuf(cur, ft_atoi_base(buf, 16));
}

static void	record_oct(t_buf **cur, char **line)
{
	int		i;
	char	buf[4];

	++*line;
	i = 0;
	ft_bzero(buf, 4);
	while (**line >= '0' && **line < '8' && i < 3)
		buf[i++] = *(*line)++;
	ft_putchar_mshbuf(cur, ft_atoi_base(buf, 8));
}

void		ft_slash(t_buf **cur, char **line)
{
	if (!**line)
		return ;
	else
		ft_putchar_mshbuf(cur, **line);
	(*line)++;
}

void		ft_dquote_slash(t_buf **cur, char **line)
{
	if (**line == 'a')
		ft_putchar_mshbuf(cur, '\a');
	else if (**line == 'b')
		ft_putchar_mshbuf(cur, '\b');
	else if (**line == 't')
		ft_putchar_mshbuf(cur, '\t');
	else if (**line == 'n')
		ft_putchar_mshbuf(cur, '\n');
	else if (**line == 'v')
		ft_putchar_mshbuf(cur, '\v');
	else if (**line == 'f')
		ft_putchar_mshbuf(cur, '\f');
	else if (**line == 'r')
		ft_putchar_mshbuf(cur, '\r');
	else if (**line == '0' || **line == 'x')
	{
		**line == '0' ? record_oct(cur, line) : record_hex(cur, line);
		return ;
	}
	else if (**line)
	{
		!ft_strchr("\"`$\\", **line) ? ft_putchar_mshbuf(cur, '\\') : 0;
		ft_putchar_mshbuf(cur, **line);
	}
	**line ? (*line)++ : 0;
}
