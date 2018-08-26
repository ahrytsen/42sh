/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:08:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/26 21:09:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>
# include <signal.h>
# include <sys/dir.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <inttypes.h>
# include <sys/wait.h>

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

/*
**	VARIABLES_MOD
*/
# define SHVAR 0
# define ENVAR 2

/*
**	JOBS_OPTIONS
*/
# define J_DEF 0
# define J_L 1
# define J_P 2

typedef struct	s_op
{
	int		v;
	int		i;
	char	*ap;
	char	*p;
	char	**exec;
}				t_op;

typedef struct	s_var
{
	char			attr;
	struct s_var	*next;
	char			*var;
}				t_var;

typedef struct	s_env
{
	char			**envar;
	t_var			*shvar;
	t_list			*setvar;
	int				st;
	pid_t			sh_pid;
	pid_t			sh_pgid;
	pid_t			pgid;
	pid_t			pid;
	t_list			*jobs;
	int				bkp_fd[3];
	int				sh_terminal;
	int				is_interactive;
	char 			**argv;
	int 			argc;
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
		assignment,
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
	int		st;
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
**				ft_argv.c
*/
char			**ft_argv_make(t_list *toks);
/*
**				ft_argv_exec.c
*/
int				ft_argv_exec(char **cmd, char *altpath, int bg);
/*
**				ft_argv_quotes.c
*/
void			ft_slash(t_buf **cur, char **line);
void			ft_dquote_slash(t_buf **cur, char **line);
void			ft_bquote_helper(t_buf **cur, char *str);
/*
**				ft_argv_utils.c
*/
void			parse_dollar(t_buf **cur, char **line);
void			ft_quote(t_buf **cur, char **line);
void			ft_bquote(t_buf **cur, char **line, uint8_t q);
char			*parse_argv(char *line);
void			ft_dquote(t_buf **cur, char **line);
/*
**				ft_ast.c
*/
int				ft_isoperator(t_token *tok);
t_ast			*ft_ast_make(t_list **toks);
/*
**				ft_ast_debug.c
*/
const char		*ft_ast_name(enum e_ast_type type);
void			ft_print_ast(t_ast *ast);
void			ft_print_toks(t_list *toks);
/*
**				ft_ast_exec.c
*/
int				ft_ast_exec(t_ast *ast);
/*
**				ft_ast_utils.c
*/
t_ast			*ft_ast_push(t_ast *ast, t_ast *node);
t_ast			*ft_ast_del(t_ast *ast, int up);
/*
**				ft_buffer.c
*/
void			ft_putstr_mshbuf(t_buf **buf, char *str, ssize_t len);
void			ft_putchar_mshbuf(t_buf **buf, char c);
char			*ft_buftostr(t_buf *buf_head);
void			*ft_free_mshbuf(t_buf *buf);
/*
**				ft_cmd_print.c
*/
void			ft_cmd_print(t_cmd *cmd);
/*
**				ft_cmdlst.c
*/
t_cmd			*ft_cmdlst_make(t_list **toks);
/*
**				ft_cmdlst_exec.c
*/
int				ft_cmdlst_exec(t_cmd *cmd, int bg);
/*
**				ft_cmdlst_utils.c
*/
void			ft_cmdlst_print(t_cmd *cmdlst);
t_cmd			*ft_cmdlst_del(t_cmd *cmdlst);
t_cmd			*ft_cmdlst_push(t_cmd *cmdlst, t_cmd *node);
/*
**				ft_heredoc.c
*/
int				ft_heredoc(t_list *toks);
/*
**				ft_init.c
*/
void			ft_fildes(int mod);
void			ft_set_sh_signal(int mod);
void			ft_init_fd(int fd);
void			ft_init(int ac, char **av);
/*
**				ft_jobs_utils.c
*/
void			ft_stop_job(t_cmd *cmd, int mod);
int				ft_control_job(t_cmd *cmd, int bg, int cont);
int				ft_status_job(int st);
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
**				ft_shell_var.c
*/
void			ft_init_shell_var(void);
int				ft_is_valid_name(char *str);
char			*ft_getenv(const char *name);
char			*ft_other_getenv(const char *name);
void			ft_var_checker(t_list *lst);
t_env			*get_environ(void);
/*
**				ft_shell_var_toolz.c
*/
void			ft_add_shvar_entry(char *entry, char attr);
t_var			*ft_get_shvar_entry(const char *name);
int				ft_rem_shvar_entry(const char *name);
int				ft_print_shvar(int mod);
/*
**				ft_shell_var_utils.c
*/
int				ft_set_tool(const char *name, const char *value,
							int overwrite, int mod);
int				ft_unset_tool(const char *name, int mod);
int				ft_setter(const char *name, const char *value);
/*
**				ft_tokenize.c
*/
t_list			*ft_tokenize(char *ln);
/*
**				ft_tokenize_tools.c
*/
int				ft_isseparator(int c);
void			ft_token_del(void *token, size_t size);
const char		*ft_tname(t_token *tok);
/*
**				ft_tokenize_utils.c
*/
int				ft_get_subsh(char **ln, t_token *token);
int				ft_skip_word(char **ln);
int				ft_skip_qoutes(char **s);
int				ft_skip_subsh(char **ln);
/*
**				ft_builtins/ft_builtins.c
*/
int				ft_echo(char **av);
int				ft_exit(char **av);
int				ft_export(char **av);
/*
**				ft_builtins/ft_bi_bg.c
*/
int				ft_bg(char **av);
/*
**				ft_builtins/ft_bi_cd.c
*/
int				ft_cd(char **av);
/*
**				ft_builtins/ft_bi_fg.c
*/
int				ft_fg(char **av);
/*
**				ft_builtins/ft_bi_jobs.c
*/
int				ft_jobs(char **av);
/*
**				ft_builtins/ft_bi_jobs_tools.c
*/
void			ft_jobs_clean_lst(t_list **jobs);
int				ft_count_jobs(t_list *jobs);
void			ft_cmd_print_colon(t_cmd *cmdlst);
void			ft_print_status(int st);
t_list			*ft_job_push_back(t_list **jobs, t_job *new_job);
/*
**				ft_builtins/ft_bi_env.c
*/
int				ft_env(char **av);
int				ft_env_op(int p);
/*
**				ft_builtins/ft_bi_export.c
*/
int				ft_export(char **av);
/*
**				ft_builtins/ft_bi_un_setenv.c
*/
int				ft_setenv(char **av);
int				ft_unsetenv(char **av);
/*
**				ft_builtins/ft_bi_un_set.c
*/
int				ft_unset(char **av);
int				ft_set_var(t_list *var, int mod);
/*
**				ft_builtins/ft_bi_history.c
*/
int				ft_history(char **av);

#endif
