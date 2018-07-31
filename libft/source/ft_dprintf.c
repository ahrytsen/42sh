/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 11:44:19 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/26 11:44:21 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**		TTTTTTTT	TT    TT	TTTTTTT 	TTTTTTT 	 TTTTTTT
**		   TT		 TT  TT 	TT	  TT	TT			TT
**		   TT		  TTTT  	TTTTTTT		TTTTTT		 TTTTTT
**		   TT		   TT   	TT  		TT			      TT
**		   TT		   TT   	TT			TTTTTTT 	TTTTTTT
*/

static int	ft_print_dec(const char **frm, va_list ap, int *flags)
{
	if (**frm == 'd' || **frm == 'i' || **frm == 'D')
		return (ft_print_signed(frm, ap, flags));
	if (**frm == 'u' || **frm == 'U')
		return (ft_print_unsigned(frm, ap, flags));
	if (**frm == 'o' || **frm == 'O')
		return (ft_print_octal(frm, ap, flags));
	if (**frm == 'x' || **frm == 'X')
		return (ft_print_hex(frm, ap, flags));
	return (ft_print_binary(frm, ap, flags));
}

static int	ft_print_type(const char **frm, va_list ap, int *flags, int ret)
{
	if (**frm == 'd' || **frm == 'i' || **frm == 'D' || **frm == 'u' ||
		**frm == 'U' || **frm == 'o' || **frm == 'O' || **frm == 'x' ||
		**frm == 'X' || **frm == 'b' || **frm == 'B')
		return (ft_print_dec(frm, ap, flags));
	if (**frm == 'p')
		return (ft_print_ptr(frm, ap, flags));
	if (**frm == 's' || **frm == 'S')
		return (ft_print_string(frm, ap, flags));
	if (**frm == 'e' || **frm == 'E' || **frm == 'f' || **frm == 'F')
		return (ft_print_science(frm, ap, flags));
	if (**frm == 'n')
	{
		(*frm)++;
		*(va_arg(ap, int *)) = ret;
		return (0);
	}
	if (**frm == 'r')
		return (ft_print_non_print(frm, ap, flags));
	if (**frm == 'k')
		return (ft_print_date(frm, ap, flags));
	if (**frm == '\0')
		return (0);
	return (ft_print_char(frm, ap, flags));
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	va_list cp;
	int		ret;
	int		flags[10];
	int		i;

	ret = 0;
	g_fd = fd;
	va_start(ap, format);
	while (*format)
		if (*format != '%' && (ret += write(g_fd, format, 1)))
			format++;
		else
		{
			format++;
			i = ft_search_dollar(&format, cp, ap);
			ft_set(&format, flags, ap);
			if (i)
				ret += ft_print_type(&format, cp, flags, ret);
			else
				ret += ft_print_type(&format, ap, flags, ret);
		}
	va_end(ap);
	return (ret);
}
