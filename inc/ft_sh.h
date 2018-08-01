/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:08:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 15:49:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ONE_SH_H
# define FT_ONE_SH_H

# include "libft.h"
# include <sys/stat.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <term.h>

/*
**	SIGNAL MODS
*/
# define S_SH 0b001
# define S_CHLD 0b010
# define S_CHLD_FG 0b100

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
int				main(void);
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

#endif
