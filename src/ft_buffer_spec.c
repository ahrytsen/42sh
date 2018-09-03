/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 10:29:44 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/02 11:56:19 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			ft_putcharq_mshbuf(t_buf **buf, char c, char *symbols)
{
	if (symbols && ft_strchr(symbols, c))
		ft_putchar_mshbuf(buf, '\\');
	ft_putchar_mshbuf(buf, c);
}

void			ft_putstrq_mshbuf(t_buf **buf, char *str,
								ssize_t len, char *symbols)
{
	if (!str || !buf || !*buf)
		return ;
	while ((len < 0 ? 1 : (len-- > 0)) && *str)
		ft_putcharq_mshbuf(buf, *str++, symbols);
}
