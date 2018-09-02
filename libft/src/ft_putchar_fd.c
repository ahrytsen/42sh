/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:16:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/30 22:04:06 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fill_buf(int c, uint8_t buf[4])
{
	int	len;

	len = -1;
	if (c <= 0x7F && (len = 1))
		buf[0] = c;
	else if (c <= 0x7FF && (len = 2))
	{
		buf[0] = (c >> 6) + 0xC0;
		buf[1] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF && (len = 3))
	{
		buf[0] = (c >> 12) + 0xE0;
		buf[1] = ((c >> 6) & 0x3F) + 0x80;
		buf[2] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0x10FFFF && (len = 4))
	{
		buf[0] = (c >> 18) + 0xF0;
		buf[1] = ((c >> 12) & 0x3F) + 0x80;
		buf[2] = ((c >> 6) & 0x3F) + 0x80;
		buf[3] = (c & 0x3F) + 0x80;
	}
	return (len);
}

int			ft_putchar_fd(int c, int fd)
{
	int		len;
	uint8_t	buf[4];

	if ((len = ft_fill_buf(c, buf)) > 0
		&& (len = write(fd, buf, len)) > 0)
		return (0);
	return (-1);
}
