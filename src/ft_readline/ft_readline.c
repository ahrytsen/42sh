/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/25 07:17:40 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_sh.h"

static int	ft_check_key(uint64_t buf)
{
	if (buf == K_AUP || buf == K_ADOWN || buf == K_RIGHT || buf == K_LEFT
		|| buf == K_HOME || buf == K_END)
		return (K_MOVE);
	else if (buf == K_ALEFT || buf == K_ARIGHT || buf == K_ABS || buf == K_ADEL)
		return (K_WORD_MOVE);
	else if (buf == K_SLEFT || buf == K_SUP || buf == K_ASLEFT
			|| buf == K_SRIGHT || buf == K_SDOWN || buf == K_ASRIGHT)
		return (K_SELECT);
	return (0);
}

static void	ft_misc_action(uint64_t buf)
{
	if (buf == K_RET)
		ft_readline_ret();
	else if (buf == K_TAB)
		ft_autocomplit(get_term()->cursor);
	else if (buf == K_BS)
		ft_back_space();
	else if (buf == K_UP || buf == K_DOWN)
		hist_move(buf);
}

static int	ft_action(uint64_t buf)
{
	if (!buf || buf == 12)
	{
		if (buf && !tputs(tgetstr("cl", NULL), 1, term_print))
			ft_redraw_line();
		return (1);
	}
	(buf != K_TAB) ? get_term()->comp_stage = -1 : 0;
	if (buf == K_DEL || buf == K_CTRL_D)
		buf = ft_del(buf);
	else if (buf == K_RET || buf == K_TAB || buf == K_BS
	|| buf == K_UP || buf == K_DOWN)
		ft_misc_action(buf);
	else if (((char*)&buf)[0] != 27 && (buf > 31 || ft_iswhitespace(buf)))
		buf = ft_add(buf);
	else if (ft_check_key(buf) == K_MOVE)
		ft_move(buf);
	else if (ft_check_key(buf) == K_WORD_MOVE)
		ft_word_action(buf);
	else if (ft_check_key(buf) == K_SELECT)
		ft_highlight(buf);
	else if (buf == K_COPY || buf == K_CUTE || buf == K_PASTE)
		buf = ft_copy_paste(buf);
	else
		write(0, "\a", 1);
	return (ft_highlight_helper(buf));
}

static int	ft_readline_helper(const int fd, char **line)
{
	int			ret;
	uint64_t	buf;

	if (!get_environ()->is_interactive)
		ret = get_next_line(fd, line);
	else
	{
		ft_terminal(T_INIT);
		hist_init();
		ft_prompt();
		while ((ret = ft_read(fd, &buf)) > 0)
			if ((ret = ft_action(buf)) <= 0 || buf == K_RET)
				break ;
		ft_terminal(T_RESTORE);
		*line = line_tostr(&get_term()->cursor, ret <= 0 ? 2 : 0);
		if (*line && ft_strchr(*line, '!'))
		{
			free(*line);
			*line = ft_rl_history_replace_mark(&get_term()->cursor);
		}
		hist_commit(ret, (int)*line);
	}
	return (ret);
}

int			ft_readline(const int fd, char **line)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	*line = NULL;
	while (ft_check_line(*line))
	{
		if ((tmp = *line))
		{
			*line = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		ret = ft_readline_helper(fd, &tmp);
		if (ret <= 0)
			break ;
		*line = ft_strextend(*line, tmp);
	}
	ret < 0 ? ft_memdel((void**)line) : 0;
	return (*line ? 1 : ret);
}
