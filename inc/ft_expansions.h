/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:22:50 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/08/20 12:40:23 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANSIONS_H
# define FT_EXPANSIONS_H

# include "libft.h"
#include <dirent.h>
#include <sys/stat.h>

typedef struct	s_char_class
{
	char		*name;
	int 		(*func)(int);
}				t_char_class;

/*
**		expand_braces.c
*/
t_list		*expand_braces(char *s, int i, char *buf);
/*
**		auxiliary_funcs.c
*/
char		*skip_quotes(char *s);
char		*check_braces(char *s);
int			check_comma(char *s);
/*
**		get_seq.c
*/
char		*get_brace_seq(char **s, t_list **lst);
char		*get_one_elem(char *s, char *buf, t_list **lst);
/*
**		get_range.c
*/
t_list		*get_valid_range(char **s, int i);
/*
**		fill_buf.c
*/
char		*put_backslash_to_buf(char *buf, int *i, char *s);
char		*put_quote_content_to_buf(char *buf, int *i, char *s);
char		*put_str_to_buf(char *buf, int *i, char *s);
char		*put_parentheses_content_to_buf(char *buf, int *i, char *s);
/*
**		regex.c
*/
int			ft_regex_str(char *pattern, char *str, char q);
/*
**		brackets.c
*/
int			ft_regex_brackets(char *pattern, char *str, char q);
/*
*		ft_strcut.c
*/
char		**ft_strcut(char const *s, char c);
/*
*		check_brackets.c
*/
char		*check_brackets(char *pattern);
#endif