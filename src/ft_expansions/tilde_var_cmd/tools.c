/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 15:34:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/04 15:35:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*ft_read_cmdsubst(int fd)
{
	t_buf	*head;
	t_buf	*cur;
	char	buf[BUFF_SIZE];
	char	*line;
	ssize_t	rd;

	if (!(head = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	cur = head;
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
		ft_putstr_mshbuf(&cur, buf, rd);
	if (!(line = ft_buftostr(head)))
		return (NULL);
	rd = ft_strlen(line) - 1;
	while (rd >= 0 && line[rd] == '\n')
		line[rd--] = '\0';
	return (line);
}
