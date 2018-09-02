/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:37:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/26 19:48:02 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static int	ft_getcurx(void)
{
	char	buf[21];
	char	*st;

	ft_bzero(buf, sizeof(buf));
	ft_dprintf(0, "\033[6n");
	if (read(0, buf, 20) == -1)
		return (-1);
	if ((st = ft_strchr(buf, ';')))
		return (ft_atoi(++st));
	return (0);
}

static void	ft_toread_heredoc(void)
{
	int			tmp;
	const char	*prompt;

	prompt = "heredoc(%s)> ";
	ft_dprintf(2, "\r%s\033[31m", tgetstr("cd", NULL));
	tmp = ft_dprintf(2, prompt, get_term()->heredoc_key);
	ft_dprintf(2, "\033[0m");
	get_term()->cury = tmp / get_term()->width;
	get_term()->curx = tmp % get_term()->width;
}

static void	ft_toread_prompt(int mod)
{
	int			tmp;
	const char	*prompt;

	prompt = "";
	if (mod == P_QUOTE || mod == P_BQUOTE)
		prompt = (mod == P_QUOTE ? "quote> " : "bquote> ");
	else if (mod == P_DQUOTE || mod == P_BSLASH)
		prompt = (mod == P_DQUOTE ? "dquote> " : "bslash> ");
	else if (mod == P_CMDSUBST || mod == P_SUBSH)
		prompt = (mod == P_SUBSH ? "subsh> " : "cmdsubst> ");
	else if (mod == P_HEREDOC)
	{
		ft_toread_heredoc();
		return ;
	}
	tmp = ft_strlen(prompt);
	get_term()->cury = tmp / get_term()->width;
	get_term()->curx = tmp % get_term()->width;
	ft_dprintf(2, "\r%s\033[31m%s\033[0m", tgetstr("cd", NULL), prompt);
}

static void	ft_user_prompt(void)
{
	int		tmp;
	int		proc;
	char	pwd[MAXPATHLEN];
	char	*ptr;

	getcwd(pwd, MAXPATHLEN);
	proc = ft_count_jobs(get_environ()->jobs);
	tmp = 3;
	ft_dprintf(2, "\r%s\033[3%cm", tgetstr("cd", NULL),
				get_environ()->st ? '1' : '2');
	tmp += ft_dprintf(2, "[%hhd] ", (char)get_environ()->st);
	if (proc)
	{
		ft_dprintf(2, "\033[36m");
		tmp += ft_dprintf(2, proc == 1 ? "{⚙} " : "{⚙: %d} ", proc) - 2;
	}
	ft_dprintf(2, "\033[33m");
	if (!(ptr = ft_getenv("PWD")) || !*ptr)
		ptr = getcwd(pwd, MAXPATHLEN);
	tmp += ft_dprintf(2, "%s ", ptr);
	ft_dprintf(2, "\033[32m$>\033[0m ");
	get_term()->cury = tmp / get_term()->width;
	get_term()->curx = tmp % get_term()->width;
}

void		ft_prompt(void)
{
	struct winsize	w;

	ioctl(get_environ()->sh_terminal, TIOCGWINSZ, &w);
	get_term()->height = w.ws_row;
	get_term()->width = w.ws_col;
	if (isatty(2))
	{
		if (ft_getcurx() != 1)
			ft_dprintf(2, "%s%%%s\n", get_term()->iv_on, get_term()->iv_off);
		get_term()->prompt ? ft_toread_prompt(get_term()->prompt)
			: ft_user_prompt();
	}
}
