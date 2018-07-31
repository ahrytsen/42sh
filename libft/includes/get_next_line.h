/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:58:00 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/16 15:58:02 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# define BUFF_SIZE 10

typedef struct	s_save
{
	char			buf[BUFF_SIZE + 1];
	struct s_save	*nxt;
	struct s_save	*prv;
	int				fd;
}				t_save;

int				get_next_line(const int fd, char **line);

#endif
