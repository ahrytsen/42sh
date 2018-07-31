/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_autocomplete_drawing.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 16:36:39 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/01 16:36:40 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static t_list	*get_list_elem(t_list *lst, int row, int col, int num_row)
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

static void		drawing_cycle(char **win_buf, t_list *lst, int *dim, int num)
{
	int		count;
	int		col;
	int		row;
	t_list	*elem;

	count = 1;
	row = 1;
	write(0, "\n", 1);
	tputs(tgetstr("cd", 0), 1, ft_putint);
	while (count <= num)
	{
		col = 0;
		while ((elem = get_list_elem(lst, row, col, dim[2])))
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

static void		get_dimensions(int *dim, int num)
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

static void		call_drawing(t_list *lst, int num, char *out, t_pos *pos)
{
	int		dim[3];
	char	*win_buf;
	size_t	i;

	dim[0] = get_max_name(lst);
	win_buf = (char *)ft_memalloc((dim[0] + 1) * num);
	get_dimensions(dim, num);
	i = pos->kur;
	while (pos->kur != pos->len)
		gsh_r_shift_right(pos);
	pos->kur = i;
	drawing_cycle(&win_buf, lst, dim, (int)num);
	write(0, win_buf, (size_t)dim[0] * num);
	gsh_prompt(1);
	tputs(out, 1, ft_putint);
	i = pos->kur;
	pos->kur = pos->len;
	while (i != pos->kur)
		gsh_r_shift_left(pos);
	free(win_buf);
}

void			reprint(t_list *lst, char *out, t_pos *pos, size_t len)
{
	int		num;

	if (!lst)
		write(0, "\a", 1);
	else if ((num = ft_lstsize(lst)) == 1)
	{
		if (pos->kur < pos->len)
			ft_memmove(out + pos->kur + lst->content_size - len - 1,
				out + pos->kur, ft_strlen(out) - pos->kur);
		ft_memcpy(out + pos->kur, lst->content + len
			, lst->content_size - len - 1);
		pos->kur += lst->content_size - len - 1;
		pos->len += lst->content_size - len - 1;
		gsh_r_redraw_line(out, pos, lst->content_size - len - 1, 1);
		if ((pos->kur + pos->prompt) % pos->col == 0)
		{
			if (pos->kur == pos->len)
				tputs(tgetstr("do", 0), 1, ft_putint);
			tputs(tgetstr("cr", 0), 1, ft_putint);
		}
	}
	else
		call_drawing(lst, (int)num, out, pos);
	ft_lstfree(&lst);
}
