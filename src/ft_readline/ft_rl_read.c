/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:28:37 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:17:35 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

ssize_t		ft_read(int fd, uint64_t *buf)
{
	ssize_t	ret;

	*buf = 0;
	ret = read(fd, buf, 1);
	if (ret != 1 || (*buf <= 0x7F && *buf != 0x1B))
		return (ret);
	else if (*buf == 0x1B)
		ret = read(fd, (uint8_t*)buf + 1, 6);
	else if (*buf >= 0xC2 && *buf <= 0xDF)
		ret = read(fd, (uint8_t*)buf + 1, 1);
	else if (*buf >= 0xE0 && *buf <= 0xEF)
		ret = read(fd, (uint8_t*)buf + 1, 2);
	else if (*buf >= 0xF0 && *buf <= 0xF4)
		ret = read(fd, (uint8_t*)buf + 1, 3);
	return (ret > 0 ? ret + 1 : ret);
}

uint64_t	ft_get_unichar(char **str)
{
	uint64_t		tmp;
	size_t			size;
	unsigned char	u;

	u = (unsigned char)**str;
	if (u >= 0xC2 && u <= 0xDF)
		size = 2;
	else if (u >= 0xE0 && u <= 0xEF)
		size = 3;
	else if (u >= 0xF0 && u <= 0xF4)
		size = 4;
	else
		size = 1;
	tmp = 0;
	strncat((char *)&tmp, *str, size);
	*str += size;
	return (tmp);
}

size_t		ft_strlen_unicode(char *str)
{
	size_t			i;
	unsigned char	u;

	i = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		u = (unsigned char)*str;
		if (u >= 0xC2 && u <= 0xDF)
			str += 2;
		else if (u >= 0xE0 && u <= 0xEF)
			str += 3;
		else if (u >= 0xF0 && u <= 0xF4)
			str += 4;
		else
			str += 1;
		i++;
	}
	return (i);
}
