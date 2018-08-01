/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty_one_sh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 20:22:12 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/07/03 17:45:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_ONE_SH_H
# define TWENTY_ONE_SH_H

# include <libft.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>

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
**	SIGNAL MODS
*/
# define S_SH 0b001
# define S_CHLD 0b010
# define S_CHLD_FG 0b100

/*
**	PROMPT
*/
# define P_USER 0
# define P_HEREDOC 1
# define P_DQUOTE 34
# define P_QUOTE 39
# define P_BSLASH 92
# define P_BQUOTE 96

/*
**	ENVIRON
*/
# define ENV_PRINT 0
# define ENV_CLEAR 1

/*
**	FILDES
*/
# define FD_BACKUP 0
# define FD_RESTORE 1

/*
**	EXEC_MOD
*/
# define EXEC_BG 0
# define EXEC_FG 1

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
}				t_hist;

typedef struct	s_term
{
	t_line	*cursor;
	t_hist	*hist;
	t_line	*st_sel;
	t_line	*end_sel;
	t_line	*buffer;
	int		prompt;
	int		curx;
	int		cury;
	char	*clear;
	char	*curmov;
	char	*cm_left;
	char	*cm_right;
	char	*iv_on;
	char	*iv_off;
	char	*del_ch;
	int		height;
	int		width;
	char	*heredoc_key;
	int		is_inter;
}				t_term;

typedef struct	s_op
{
	int		v;
	int		i;
	char	*ap;
	char	*p;
	char	**exec;
}				t_op;

typedef struct	s_env
{
	char			**env;
	int				st;
	pid_t			sh_pid;
	pid_t			sh_pgid;
	pid_t			pgid;
	pid_t			pid;
	t_list			*jobs;
	int				bkp_fd[3];
	struct termios	savetty;
	struct termios	work_tty;
	int				sh_terminal;
	int				is_interactive;
}				t_env;

typedef struct	s_builtins
{
	char	*cmd;
	int		(*ft_builtin)();
}				t_builtins;

typedef struct	s_buf
{
	size_t			id;
	size_t			len;
	char			str[BUFF_SIZE];
	struct s_buf	*next;
}				t_buf;

typedef enum	e_token_type
{
	blank,
	word,
	pipeline,
	bg_op,
	semicolon,
	and,
	or,
	heredoc,
	heredoc_t,
	herestr,
	open_file,
	read_out,
	read_out_pipe,
	read_out_apend,
	read_in,
	read_in_and,
	read_out_and,
	and_read_out
}				t_type;

typedef struct	s_redir
{
	int		cls;
	int		left;
	int		nbr;
	char	*hd;
	char	*right;
}				t_redir;
typedef union	u_data
{
	char		*word;
	t_redir		redir;
}				t_data;
typedef struct	s_token
{
	t_type	type;
	t_data	data;
}				t_token;

typedef struct	s_cmd
{
	char			**av;
	t_list			*toks;
	pid_t			pid;
	int				ret;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct	s_job
{
	pid_t			pgid;
	t_cmd			*cmd;
}				t_job;

typedef enum	e_ast_node_type
{
	cmd = word,
	ast_and = and,
	ast_or = or,
	ast_bg = bg_op,
	ast_smcln = semicolon
}				t_ast_type;

typedef struct	s_ast
{
	t_list			*toks;
	t_ast_type		type;
	pid_t			pid;
	int				bg;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*prev;
}				t_ast;

/*
**				main.c
*/
//int				main(void);
int				main_loop(void);
/*
**				init.c
*/
void			ft_fildes(int mod);
void			ft_set_sh_signal(int mod);
void			ft_init(void);
/*
**				ft_tokenize.c
*/
t_list			*ft_tokenize(char *ln);
/*
**				ft_tokenize_utils.c
*/
void			ft_token_del(void *token, size_t size);
int				ft_isseparator(int c);
int				ft_check_redir(t_token *prev, t_token *next, char *ln);
void			ft_skip_slash(char **s);
int				ft_skip_qoutes(char **s);
/*
**				ft_heredoc.c
*/
int				ft_heredoc(t_list *toks);
/*
**				ft_cmdlst.c
*/
t_cmd			*ft_cmdlst_make(t_list **toks);
/*
**				ft_cmdlst_utils.c
*/
void			ft_cmdlst_print(t_cmd *cmdlst);
t_cmd			*ft_cmdlst_del(t_cmd *cmdlst);
t_cmd			*ft_cmdlst_push(t_cmd *cmdlst, t_cmd *node);
/*
**				ft_cmdlst_exec.c
*/
int				ft_cmdlst_exec(t_cmd *cmd, int bg);
/*
**				ft_ast.c
*/
char			*ft_tname(int type);
t_ast			*ft_ast_make(t_list **toks);
/*
**				ft_ast_utils.c
*/
t_ast			*ft_ast_push(t_ast *ast, t_ast *node);
t_ast			*ft_ast_del(t_ast *ast, int up);
/*
**				ft_ast_exec.c
*/
int				ft_ast_exec(t_ast *ast);
/*
**				ft_argv.c
*/
char			**ft_argv_make(t_list *toks);
/*
**				ft_argv_utils.c
*/
void			parse_dollar(t_buf **cur, char **line);
void			ft_quote(t_buf **cur, char **line);
void			ft_bquote(t_buf **cur, char **line, uint8_t q);
char			*parse_argv(char *line);
/*
**				ft_argv_quotes.c
*/
void			ft_slash(t_buf **cur, char **line);
void			ft_dquote_slash(t_buf **cur, char **line);
void			ft_bquote_helper(t_buf **cur, char *str);
/*
**				ft_argv_exec.c
*/
int				ft_argv_exec(char **cmd, char *altpath, int bg);
/*
**				ft_redirection.c
*/
int				ft_redirection(t_list *toks);
void			ft_redirection_close(t_list *toks);
/*
**				ft_redirection_utils.c
*/
int				ft_redir_right_param(t_token *tok);
/*
**				ft_jobs_utils.c
*/
void			ft_stop_job(t_cmd *cmd, int mod);
int				ft_control_job(t_cmd *cmd, int bg, int cont);
int				ft_status_job(int st);
/*
**				builtins/builtins.c
*/
int				ft_echo(char **av);
int				ft_setenv_builtin(char **av);
int				ft_unsetenv_builtin(char **av);
int				ft_exit(char **av);
/*
**				builtins/ft_cd.c
*/
int				ft_cd(char **av);
/*
**				builtins/ft_fg.c
*/
int				ft_count_fg(t_list *proc);
int				ft_fg(char **av);
/*
**				builtins/env_builtin.c
*/
int				ft_env(char **av);
int				ft_env_op(int p);
/*
**				env_utils.c
*/
t_env			*get_environ(void);
char			*ft_getenv(const char *name);
int				ft_setenv(const char *name, const char *value, int overwrite);
int				ft_unsetenv(const char *name);
/*
**				ft_buffer.c
*/
void			ft_putstr_mshbuf(t_buf **buf, char *str, ssize_t len);
void			ft_putchar_mshbuf(t_buf **buf, char c);
char			*ft_buftostr(t_buf *buf_head);
void			*ft_free_mshbuf(t_buf *buf);
/*
**				ft_readline/ft_readline.c
*/
int				ft_readline(const int fd, char **line);
/*
**				ft_readline/rl_init.c
*/
void			ft_terminal(int mod);
int				ft_is_interrupted(void);
/*
**				ft_readline/ft_readline_action.c
*/
void			ft_back_space(void);
void			ft_move(uint64_t buf);
int				ft_add(uint64_t buf);
int				ft_del(uint64_t buf);
void			ft_word_action(uint64_t buf);
/*
**				ft_readline/ft_readline_helper.c
*/
int				term_print(int c);
t_term			*get_term(void);
void			ft_readline_ret(void);
void			ft_print_tail(t_line *cursor);
void			ft_redraw_line(void);
/*
**				ft_readline/ft_read.c
*/
ssize_t			ft_read(int fd, uint64_t *buf);
/*
**				ft_readline/ft_cursor.c
*/
void			ft_curleft(int mod);
void			ft_curright(int mod);
void			ft_curnleft(int mod, int n);
void			ft_curnright(int mod, int n);
void			ft_curhome(void);
/*
**				ft_readline/line.c
*/
t_line			*copy_line(t_line *line);
char			*line_tostr(t_line **cursor, int mod);
int				line_bs(t_line *cursor);
int				line_add(t_line *cursor, uint64_t ch);
/*
**				ft_readline/line_edit.c
*/
void			line_cute(void);
int				line_copy(void);
void			line_paste(void);
int				ft_copy_paste(uint64_t buf);
/*
**				ft_readline/ft_autocomplit.c
*/
void			ft_autocomplit(t_line *cursor);
/*
**				ft_readline/ft_history.c
*/
int				hist_init(void);
void			hist_move(uint64_t buf);
void			clean_hist(void);
void			hist_commit(int st);
/*
**				ft_readline/ft_highlight.c
*/
void			ft_highlight(uint64_t buf);
uint64_t		ft_highlight_helper(uint64_t buf);
/*
**				ft_readline/ft_prompt.c
*/
void			ft_prompt(void);
/*
**				ft_readline/ft_check_line.c
*/
int				ft_check_line(char *ln);

#endif
