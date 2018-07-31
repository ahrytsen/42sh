/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_cut_copy_paste.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:21:52 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/29 14:21:54 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void	gsh_r_paste_buffer(char *out, t_pos *pos)
{
	size_t size;

	size = ft_strlen(g_buffer);
	if (pos->kur < pos->len)
		ft_memmove(out + pos->kur + size, out + pos->kur, pos->len
			- pos->kur);
	ft_memcpy(out + pos->kur, g_buffer, size);
	pos->kur += size;
	pos->len += size;
	gsh_r_redraw_line(out, pos, size, 1);
	if ((pos->kur + pos->prompt) % pos->col == 0)
	{
		if (pos->kur == pos->len)
			tputs(tgetstr("do", 0), 1, ft_putint);
		tputs(tgetstr("cr", 0), 1, ft_putint);
	}
}

static void	gsh_r_copy_line(uintmax_t d, char *out, t_pos *pos)
{
	if (d != K_SHFT_UP)
		ft_bzero(g_buffer, LINE_SIZE);
	if (d == K_SHFT_UP)
		gsh_r_paste_buffer(out, pos);
	else if (d == K_SHFT_DWN)
		ft_strcpy(g_buffer, out);
	else if (d == K_SHFT_RGHT)
		ft_strcpy(g_buffer, out + pos->kur);
	else if (d == K_SHFT_LFT)
		ft_strncpy(g_buffer, out, pos->kur);
}

static void	gsh_r_cut_left_right(uintmax_t d, char *out, t_pos *pos)
{
	ft_bzero(g_buffer, LINE_SIZE);
	if (d == K_SHFT_ALT_RGHT)
	{
		ft_strcpy(g_buffer, out + pos->kur);
		tputs(tgetstr("cd", 0), 1, ft_putint);
		pos->len = pos->kur;
		ft_bzero((void *)(out + pos->kur), LINE_SIZE - pos->kur);
	}
	else
	{
		ft_strncpy(g_buffer, out, pos->kur);
		ft_memmove(out, out + pos->kur, pos->len - pos->kur);
		pos->len -= pos->kur;
		while (pos->kur)
			gsh_r_shift_left(pos);
		ft_bzero((void *)(out + pos->len), LINE_SIZE - pos->len);
		gsh_r_redraw_line(out, pos, 0, 1);
	}
}

void		gsh_r_cut_copy_paste(t_ych u, char *out, t_pos *pos)
{
	if (u.c[3] == ';' && u.c[4] == '2')
		gsh_r_copy_line(u.d, out, pos);
	else if (u.c[3] == ';' && u.c[4] == '1' && u.c[5] == '0')
	{
		if (u.d == K_SHFT_ALT_UP)
		{
			gsh_r_home_end_tab('H', NULL, pos);
			tputs(tgetstr("cd", 0), 1, ft_putint);
			ft_bzero((void *)out, LINE_SIZE);
			ft_strcpy(out, g_buffer);
			tputs(out, 1, ft_putint);
			pos->len = ft_strlen(out);
			pos->kur = pos->len;
		}
		else if (u.d == K_SHFT_ALT_DWN)
		{
			ft_strcpy(g_buffer, out);
			ft_bzero((void *)out, LINE_SIZE);
			gsh_r_home_end_tab('H', NULL, pos);
			tputs(tgetstr("cd", 0), 1, ft_putint);
			pos->len = 0;
		}
		else if (u.d == K_SHFT_ALT_RGHT || u.d == K_SHFT_ALT_LFT)
			gsh_r_cut_left_right(u.d, out, pos);
	}
}
