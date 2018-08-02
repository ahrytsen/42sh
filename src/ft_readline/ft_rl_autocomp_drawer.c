/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomp_drawer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:08:06 by dlinkin           #+#    #+#             */
/*   Updated: 2018/08/02 15:08:07 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static t_list	*rl_get_list_elem(t_list *lst, int row, int col, int num_row)
{
	int i;

	i = 1;
	while (lst)
	{
		if (i == row + col * num_row)
			break ;
		i++;
		lst = lst->next;
	}
	return (lst);
}

static void		rl_drawing_cycle(char **win_buf, t_list *lst, int *dim, int num)
{
	int		count;
	int		col;
	int		row;
	t_list	*elem;

	count = 1;
	row = 1;
	write(0, "\n", 1);
	tputs(tgetstr("cd", 0), 1, term_print);
	while (count <= num)
	{
		col = 0;
		while ((elem = rl_get_list_elem(lst, row, col, dim[2])))
		{
			ft_strcat(*win_buf, (char *)elem->content);
			if (col + 1 != dim[1])
				ft_memset((void *)(*win_buf + ft_strlen(*win_buf)), ' ',
					dim[0] - (int)elem->content_size + 1);
			count++;
			col++;
		}
		ft_strcat(*win_buf, "\n");
		col + 1 == dim[1] ? (dim[1]--) : 0;
		row++;
	}
}

/*
**	dim[] - dimensions: 0 - max name, 1 - columns, 2 - rows, 3 - mod
*/

static void		rl_get_dimensions(int *dim, int num)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (num == 0)
	{
		dim[1] = 0;
		return ;
	}
	dim[1] = 1;
	while ((dim[1] + 1) * dim[0] < ws.ws_col)
	{
		if (dim[1] > num)
			break ;
		dim[1]++;
	}
	dim[2] = num / dim[1];
	while (dim[1] * dim[2] < num)
		dim[2]++;
	while ((dim[1] - 1) * dim[2] >= num)
		dim[1]--;
}

static int		rl_get_max_name(t_list *lst)
{
	size_t max;

	max = 0;
	while (lst)
	{
		if (max < lst->content_size - 1)
			max = lst->content_size - 1;
		lst = lst->next;
	}
	max += 2;
	return ((int)max);
}

char			*ft_rl_match_drawer(t_list *lst, char *str)
{
	int		num;
	int		dim[3];
	char	*win_buf;
	char	*ptr;

	ptr = NULL;
	if (!lst)
		write(0, "\a", 1);
	else if ((num = (int)ft_lstsize(lst)) == 1)
		ptr = ft_strdup(lst->content + ft_strlen(str));
	else
	{
		dim[0] = rl_get_max_name(lst);
		win_buf = (char *)ft_memalloc((dim[0] + 1) * num);
		rl_get_dimensions(dim, num);
		rl_drawing_cycle(&win_buf, lst, dim, (int)num);
		write(0, win_buf, (size_t)dim[0] * num);
		free(win_buf);
		ft_redraw_line();
	}
	ft_lstfree(&lst);
	return (ptr);
}
