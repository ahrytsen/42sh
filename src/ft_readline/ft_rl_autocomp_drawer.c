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

/*
**	i[]: 0 - column, 1 - row, 2 - count
*/

static void		rl_drawing_cycle(char **buf, t_list *lst, int *dim)
{
	int		i[3];
	t_list	*elem;

	i[2] = 1;
	i[1] = 1;
	write(0, "\n", 1);
	tputs(tgetstr("cd", 0), 1, term_print);
	while (i[2] <= dim[3])
	{
		i[0] = 0;
		while ((elem = rl_get_list_elem(lst, i[1], i[0], dim[2])))
		{
			ft_strcat(*buf, (char *)elem->content);
			(i[0] + 1 != dim[1]) ? ft_memset((void *)(*buf + ft_strlen(*buf))
				, ' ', dim[0] - (int)elem->content_size + 1) : 0;
			i[2]++;
			i[0]++;
		}
		ft_strcat(*buf, "\n");
		i[0] + 1 == dim[1] ? (dim[1]--) : 0;
		i[1]++;
	}
	i[0] = get_term()->cury + 1;
	while (--i[0])
		ft_strcat(*buf, "\n");
}

/*
**	dim[]: 0 - max name, 1 - columns, 2 - rows, 3 - list size
*/

static void		rl_get_dimensions(int *dim)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (dim[3] == 0)
	{
		dim[1] = 0;
		return ;
	}
	dim[1] = 1;
	while ((dim[1] + 1) * dim[0] < ws.ws_col)
	{
		if (dim[1] > dim[3])
			break ;
		dim[1]++;
	}
	dim[2] = dim[3] / dim[1];
	while (dim[1] * dim[2] < dim[3])
		dim[2]++;
	while ((dim[1] - 1) * dim[2] >= dim[3])
		dim[1]--;
}

static int		rl_get_max_name(t_list *lst)
{
	size_t max;
	size_t size;

	max = 0;
	while (lst)
	{
		size = ft_strlen_unicode((char *)lst->content) - 1;
		if (max < size)
			max = size;
		lst = lst->next;
	}
	max += 2;
	return ((int)max);
}

char			*ft_rl_match_drawer(t_list *lst, char *str)
{
	int		dim[4];
	char	*buf;
	char	*ptr;

	ptr = NULL;
	if ((dim[3] = (int)ft_lstsize(lst)) == 1)
	{
		get_term()->comp_stage = -1;
		ptr = ft_strdup(lst->content + ft_strlen(str));
	}
	else if (get_term()->comp_stage == -1)
	{
		dim[0] = rl_get_max_name(lst);
		buf = (char *)ft_memalloc((dim[0] + 1) * dim[3] + get_term()->cury + 1);
		rl_get_dimensions(dim);
		rl_drawing_cycle(&buf, lst, dim);
		ft_putstr_fd(buf, 0);
		free(buf);
		ft_redraw_line();
		get_term()->comp_stage = 0;
	}
	else
		ptr = ft_rl_autocomp_switcher(lst, str);
	ft_lstfree(&lst);
	return (ptr);
}
