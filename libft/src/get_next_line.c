/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 13:08:50 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/03 20:01:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_fd_buff(const int fd, t_list **fd_lst)
{
	char	*fd_buff;
	t_list	*tmp;

	while (*fd_lst)
	{
		if ((*fd_lst)->content_size == (size_t)fd)
		{
			fd_buff = (*fd_lst)->content;
			tmp = *fd_lst;
			*fd_lst = (*fd_lst)->next;
			free(tmp);
			return (fd_buff);
		}
		fd_lst = &(*fd_lst)->next;
	}
	return (NULL);
}

static int	ft_save_fd_buff(const int fd, t_list **fd_lst, char *fd_buff)
{
	int		ret;
	char	*start;
	t_list	*new_fd;

	ret = 0;
	if (ft_strlen(fd_buff) - ft_strlen_c(fd_buff, '\n') > 1)
	{
		start = ft_strchr(fd_buff, '\n') + 1;
		if (!(new_fd = (t_list*)malloc(sizeof(t_list)))
			|| !(new_fd->content = ft_strsub(start, 0, ft_strlen(start))))
		{
			free(new_fd);
			ret = 1;
		}
		else
		{
			new_fd->next = NULL;
			new_fd->content_size = fd;
			ft_lstadd_end(fd_lst, new_fd);
		}
	}
	free(fd_buff);
	return (ret);
}

static int	read_to_newline(const int fd, char **fd_buff)
{
	char			*read_b;
	char			*tmp;
	ssize_t			count;

	if (!(read_b = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	while ((count = read(fd, read_b, BUFF_SIZE)) > 0)
	{
		tmp = *fd_buff;
		read_b[count] = '\0';
		if (!(*fd_buff = ft_strjoin(*fd_buff, read_b)))
		{
			count = -1;
			*fd_buff = tmp;
			break ;
		}
		free(tmp);
		if (ft_strchr(read_b, '\n'))
			break ;
	}
	free(read_b);
	return (count < 0 ? 1 : 0);
}

int			get_next_line(const int fd, char **line)
{
	char			*fd_buff;
	static t_list	*fd_lst;

	if (!line || fd < 0)
		return (-1);
	*line = NULL;
	fd_buff = ft_get_fd_buff(fd, &fd_lst);
	if ((!fd_buff || !ft_strchr(fd_buff, '\n'))
		&& read_to_newline(fd, &fd_buff))
	{
		free(fd_buff);
		return (-1);
	}
	if (!fd_buff)
		return (0);
	if (!(*line = ft_strsub(fd_buff, 0, ft_strlen_c(fd_buff, '\n'))))
	{
		free(fd_buff);
		return (-1);
	}
	if (ft_save_fd_buff(fd, &fd_lst, fd_buff))
		return (-1);
	return (1);
}
