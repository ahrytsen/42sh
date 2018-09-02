/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 17:38:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/27 20:53:36 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "libft.h"
# include <sys/ioctl.h>
# include <signal.h>
# include <term.h>
# include <inttypes.h>

/*
**	KEY BINDINGS
*/
# define K_UP 0X415B1B
# define K_AUP 0X41393B315B1B
# define K_SUP 0X41323B315B1B
# define K_DOWN 0X425B1B
# define K_ADOWN 0X42393B315B1B
# define K_SDOWN 0X42323B315B1B
# define K_LEFT 0X445B1B
# define K_ALEFT 0X621B
# define K_SLEFT 0X44323B315B1B
# define K_ASLEFT 0X4430313B315B1B
# define K_RIGHT 0X435B1B
# define K_ARIGHT 0X661B
# define K_SRIGHT 0X43323B315B1B
# define K_ASRIGHT 0X4330313B315B1B
# define K_HOME 0X485B1B
# define K_END 0X465B1B
# define K_BS 0X7F
# define K_ABS 0X7F1B
# define K_DEL 0X7E335B1B
# define K_CTRL_D 0X4
# define K_ADEL 0X641B
# define K_SPC 0X20
# define K_RET 0XA
# define K_SRCH 0X6
# define K_ESC 0X1B
# define K_TAB 0X9
# define K_CUTE 0X781B
# define K_COPY 0X631B
# define K_PASTE 0X761B
# define K_MOVE 1
# define K_WORD_MOVE 2
# define K_SELECT 3

/*
**	TERMINAL MODS
*/
# define T_INIT 1
# define T_RESTORE 0

/*
**	PROMPT
*/
# define P_USER 0
# define P_HEREDOC 1
# define P_DQUOTE 34
# define P_QUOTE 39
# define P_BSLASH 92
# define P_BQUOTE 96
# define P_CMDSUBST 2
# define P_SUBSH 3
# define P_AND 4
# define P_OR 5
# define P_CURSH 6
# define P_CASE 7
# define P_FOR 8
# define P_IF 9
# define P_UNTIL 10
# define P_WHILE 11

typedef struct	s_line
{
	uint64_t		ch;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

typedef struct	s_hist
{
	t_line			*line;
	t_line			*tmp;
	struct s_hist	*next;
	struct s_hist	*prev;
	unsigned		no;
}				t_hist;

typedef struct	s_term
{
	t_line			*cursor;
	t_hist			*hist;
	t_line			*st_sel;
	t_line			*end_sel;
	t_line			*buffer;
	int				prompt;
	int				curx;
	int				cury;
	char			*clear;
	char			*curmov;
	char			*cm_left;
	char			*cm_right;
	char			*iv_on;
	char			*iv_off;
	char			*del_ch;
	int				height;
	int				width;
	char			*heredoc_key;
	int				is_inter;
	struct termios	savetty;
	struct termios	work_tty;
	int				comp_stage;
	int				comp_erase;
	int				hist_max_size;
}				t_term;

/*
**				ft_readline/ft_readline.c
*/
int				ft_readline(const int fd, char **line);
/*
**				ft_readline/ft_rl_init.c
*/
void			ft_terminal(int mod);
int				ft_is_interrupted(void);
/*
**				ft_readline/ft_rl_action.c
*/
void			ft_back_space(void);
void			ft_move(uint64_t buf);
int				ft_add(uint64_t buf);
int				ft_del(uint64_t buf);
void			ft_word_action(uint64_t buf);
/*
**				ft_readline/ft_rl_helper.c
*/
int				term_print(int c);
t_term			*get_term(void);
void			ft_readline_ret(void);
void			ft_print_tail(t_line *cursor);
void			ft_redraw_line(void);
/*
**				ft_readline/ft_rl_read.c
*/
ssize_t			ft_read(int fd, uint64_t *buf);
uint64_t		ft_get_unichar(char **str);
size_t			ft_strlen_unicode(char *str);
/*
**				ft_readline/ft_rl_cursor.c
*/
void			ft_curleft(int mod);
void			ft_curright(int mod);
void			ft_curnleft(int mod, int n);
void			ft_curnright(int mod, int n);
void			ft_curhome(void);
/*
**				ft_readline/ft_rl_line.c
*/
t_line			*copy_line(t_line *line);
char			*line_tostr(t_line **cursor, int mod);
int				line_bs(t_line *cursor);
int				line_add(t_line *cursor, uint64_t ch);
/*
**				ft_readline/ft_rl_line_edit.c
*/
void			line_cute(void);
int				line_copy(void);
void			line_paste(void);
int				ft_copy_paste(uint64_t buf);
/*
**				ft_readline/ft_rl_autocomplit.c
*/
void			ft_autocomplit(t_line *cursor);
char			*ft_rl_autocomp_switcher(t_list *lst, char *str);
/*
**				ft_readline/ft_rl_autocomp_filenames.c
*/
char			*ft_rl_search_filename(char *str, size_t len);
/*
**				ft_readline/ft_rl_autocomp_drawer.c
*/
char			*ft_rl_match_drawer(t_list *lst, char *str);
/*
**				ft_readline/ft_rl_autocomp_commands_and_var.c
*/
char			*ft_rl_search_command(char *str, size_t len);
char			*ft_rl_search_varname(char *str, size_t len);
/*
**				ft_readline/ft_rl_history.c
*/
int				hist_init(void);
void			hist_move(uint64_t buf);
void			clean_hist(void);
void			hist_commit(int st, int i);
/*
**				ft_readline/ft_rl_highlight.c
*/
void			ft_highlight(uint64_t buf);
uint64_t		ft_highlight_helper(uint64_t buf);
/*
**				ft_readline/ft_rl_prompt.c
*/
void			ft_prompt(void);
/*
**				ft_readline/ft_rl_check_line.c
*/
int				ft_rl_skip_subsh(char **ln);
int				ft_check_line(char *ln);
/*
**				ft_readline/ft_rl_exclamation.c
*/
char			*ft_rl_history_replace_mark(t_line **cur);

#endif
