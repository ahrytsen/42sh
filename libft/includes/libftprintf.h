/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:17:38 by dlinkin           #+#    #+#             */
/*   Updated: 2017/11/27 12:17:40 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <inttypes.h>
# include <stdlib.h>
# include <wchar.h>

typedef union	u_soviet
{
	double		fl;
	uintmax_t	dw;
}				t_soviet;

typedef struct	s_date
{
	int			yy;
	int			mon;
	int			dd;
	int			hh;
	int			mm;
	int			ss;
}				t_date;

int				g_fd;

void			ft_put_sg(long long int n, int *flags, int len);
void			ft_put_oct(unsigned long long n, int *flags);
void			ft_put_un(unsigned long long n, int *flags, int len);
void			ft_put_hex(unsigned long long n,
	char *str, int *flags, int len);
int				ft_sg_nbrlen(long long int nbr, int apox);
unsigned		ft_un_nbrlen(unsigned long long nbr, unsigned base, int apox);
void			ft_set(const char **format, int *flags, va_list ap);
int				ft_putlen(char *str, int *flags);
void			ft_wchar_len(wchar_t *s, int *flags);
int				ft_strlen_null(char *s);
void			ft_print_length(int *flags);
void			ft_print_width(int *flags);
int				ft_print_signed(const char **frm, va_list ap, int *flags);
int				ft_print_octal(const char **frm, va_list ap, int *flags);
int				ft_print_unsigned(const char **frm, va_list ap, int *flags);
int				ft_print_hex(const char **frm, va_list ap, int *flags);
int				ft_print_ptr(const char **frm, va_list ap, int *flags);
int				ft_print_string(const char **frm, va_list ap, int *flags);
int				ft_print_char(const char **frm, va_list ap, int *flags);
int				ft_search_dollar(const char **frm, va_list cp, va_list ap);
int				ft_print_science(const char **frm, va_list ap, int *flags);
void			ft_put_dbl(double n, int *flags, int i, int len);
void			ft_put_rem(double n, int *flags);
int				is_nan_inf_zero(double d);
int				ft_dbl_len(double d, int *flags);
double			ft_set_correction(double d, int prec);
int				non_printable(double d, int *flags, char c);
int				science_exp(const char **frm, va_list ap, int *flgs);
int				science_float(const char **frm, va_list ap, int *flgs);
int				ft_print_binary(const char **frm, va_list ap, int *flags);
int				ft_print_date(const char **frm, va_list ap, int *flags);
int				ft_print_non_print(const char **frm, va_list ap, int *flags);

#endif
