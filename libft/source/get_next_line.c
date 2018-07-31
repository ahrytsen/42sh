/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:12:42 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/19 11:12:45 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	v.2
*/

static char	*ft_gnl_realloc(size_t new_size, size_t old_size, char *ptr)
{
	char	*tmp;

	if (new_size <= old_size)
		return (ptr);
	if (!ptr)
		return (ft_memalloc(new_size + 1));
	if (!(tmp = (char *)malloc(sizeof(char) * (new_size + 1))))
		return (NULL);
	while (old_size)
	{
		tmp[old_size] = ptr[old_size];
		old_size--;
	}
	tmp[old_size] = ptr[old_size];
	free(ptr);
	return (tmp);
}

static int	ft_check(char *buf, char **line)
{
	size_t	len;
	char	*ptr;

	if (buf[0])
	{
		len = ft_strlen(*line);
		if ((ptr = ft_strchr(buf, '\n')))
		{
			*line = ft_gnl_realloc(len + ptr - buf + 1, len, *line);
			*line = ft_strncat(*line, buf, ptr - buf);
			(*line)[len + ptr - buf] = '\0';
			buf = ft_strncpy(buf, ptr + 1, BUFF_SIZE + 1);
			return (1);
		}
		*line = ft_gnl_realloc(len + ft_strlen(buf) + 1, len, *line);
		(*line) = ft_strcat((*line), buf);
		ft_bzero(buf, BUFF_SIZE);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || !line || BUFF_SIZE == 0)
		return (-1);
	*line = NULL;
	while (!(ft_check(buf, line)))
	{
		ret = read(fd, (void *)buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0 && !(*line))
			return (0);
		if (ret == 0 && *line)
			return (1);
		buf[ret] = '\0';
	}
	return (1);
}
