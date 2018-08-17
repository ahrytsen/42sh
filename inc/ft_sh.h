/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:08:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/17 19:32:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

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
	char			**envar;
	char			**shvar;
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

typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;

typedef struct	s_token
{
	enum	e_token_type
	{
		blank,
		redir,
		word,
		res_word,
		pipeln,
		subsh,
		nl,
		bg_op,
		semi,
		dsemi,
		and,
		or
	}		type;
	char	*word;
	union		u_data
	{
		enum	e_rsrv_word_type
		{
			not,
			brace_on,
			brace_off,
			_case,
			_do,
			done,
			elif,
			_else,
			esac,
			fi,
			_for,
			_if,
			in,
			then,
			until,
			_while
		}		res_word_type;
		t_ast	*sub_ast;
		struct	s_redir
		{
			enum	e_redir_type
			{
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
			}		type;
			int		cls;
			int		left;
			int		nbr;
			char	*hd;
			char	*right;
		}		redir;
	}		data;
}				t_token;

struct			s_ast
{
	enum	e_ast_type
	{
		cmd,
		ast_and,
		ast_or,
		ast_bg,
		ast_semi,
		ast_dsemi
	}		type;
	t_list	*toks;
	pid_t	pid;
	int		bg;
	struct		s_cmd
	{
		enum	e_cmd_type
		{
			cmd_smpl,
			cmd_subsh,
			cmd_not,
			cmd_grp,
			cmd_case,
			cmd_for,
			cmd_if,
			cmd_until,
			cmd_while
		}		type;
		char	**av;
		t_list	*toks;
		pid_t	pid;
		int		ret;
		int		p_in;
		int		p_out;
		t_cmd	*next;
		t_cmd	*prev;
	}		*cmd;
	t_ast	*left;
	t_ast	*right;
	t_ast	*prev;
};

typedef struct	s_job
{
	pid_t	pgid;
	t_cmd	*cmd;
}				t_job;

/*
**				ft_argv_exec.c
*/
extern const t_builtins	g_builtin[];

/*
**				main.c
*/
int				main_loop(int fd);
/*
**				init.c
*/
void			ft_fildes(int mod);
void			ft_set_sh_signal(int mod);
void			ft_init_fd(int fd);
void			ft_init(void);
/*
**				ft_tokenize.c
*/
t_list			*ft_tokenize(char *ln);
/*
**				ft_tokenize_utils.c
*/
int				ft_get_subsh(char **ln, t_token *token);
int				ft_skip_word(char **ln);
int				ft_skip_qoutes(char **s);
int				ft_skip_subsh(char **ln);
/*
**				ft_tokenize_tools.c
*/
int				ft_isseparator(int c);
void			ft_token_del(void *token, size_t size);
const char		*ft_tname(t_token *tok);
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
int				ft_isoperator(t_token *tok);
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
**				ft_ast_debug.c
*/
const char		*ft_ast_name(enum e_ast_type type);
void			ft_print_ast(t_ast *ast);
void			ft_print_toks(t_list *toks);
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
int				ft_redir_check(t_token *prev, t_token *next, char *ln);
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
