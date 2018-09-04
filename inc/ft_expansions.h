/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:22:50 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/09/04 15:37:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANSIONS_H
# define FT_EXPANSIONS_H

# include "ft_sh.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>

typedef struct	s_char_class
{
	char	*name;
	int		(*func)(int);
}				t_char_class;

/*
**				ft_expansions/brace/expand_braces.c
*/
t_list			*expand_braces(char *s, int i, char *buf);
t_list			*brace_expansion(t_list *lst);
/*
**				ft_expansions/brace/auxiliary_funcs.c
*/
char			*skip_quotes(char *s);
char			*check_braces(char *s);
int				check_comma(char *s);
/*
**				ft_expansions/brace/get_seq.c
*/
char			*get_brace_seq(char **s, t_list **lst);
char			*get_one_elem(char *s, char *buf, t_list **lst);
/*
**				ft_expansions/brace/get_range.c
*/
t_list			*get_valid_range(char **s, int i);
/*
**				ft_expansions/brace/fill_buf.c
*/
char			*put_backslash_to_buf(char *buf, int *i, char *s);
char			*put_quote_content_to_buf(char *buf, int *i, char *s);
char			*put_str_to_buf(char *buf, int *i, char *s);
char			*put_parentheses_content_to_buf(char *buf, int *i, char *s);
/*
**				ft_expansions/pathname/regex.c
*/
int				ft_regex_str(char *pat, char *str, char q);
t_list			*expand_pathname(t_list *lst);
/*
**				ft_expansions/pathname/brackets.c
*/
int				ft_regex_brackets(char *pattern, char *str, char q);
/*
**				ft_expansions/pathname/ft_strcut.c
*/
char			**ft_strcut(char *s, char c);
/*
**				ft_expansions/pathname/check_brackets.c
*/
char			*check_brackets(char *pattern);
/*
**				ft_expansions/tilde_var_cmd/substitute_variable.c
*/
void			record_var(t_buf **buf, char **s, char *symbols);
void			substitute_variable(t_list *lst);
/*
**				ft_expansions/tilde_var_cmd/tilde.c
*/
void			expand_tilde(t_buf **buf, char **s);
/*
**				ft_expansions/tilde_var_cmd/substitute_cmd.c
*/
void			substitute_cmd(t_buf **buf, char **s, char *symbols);
void			ft_bquote(t_buf **cur, char **line, uint8_t q);
/*
**				ft_expansions/tilde_var_cmd/tools.c
*/
char			*ft_read_cmdsubst(int fd);
/*
**				ft_expansions/quote/quote_removal.c
*/
void			ft_quote(t_buf **cur, char **line);
void			ft_dquote(t_buf **cur, char **line);
void			remove_quotes(t_list *lst);
/*
**				ft_expansions/quote/bslash_removal.c
*/
void			ft_slash(t_buf **cur, char **line);
void			ft_dquote_slash(t_buf **cur, char **line);
/*
**				ft_expansions/field/field_splitting.c
*/
t_list			*field_splitting(t_list *lst);

#endif
