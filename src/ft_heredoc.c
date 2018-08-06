/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:00:10 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/01 14:33:16 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"

static char	*parse_heredoc(char *line, int mod, int *f)
{
	char	*tmp;
	t_buf	*head;
	t_buf	*cur;

	tmp = line;
	if (!line || !(head = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	cur = head;
	while (*line)
		if (*line == '\\' && mod <= 1 && line++)
			ft_slash(&cur, &line);
		else if (*line == '$' && (mod == 1 || mod == 2) && line++)
			parse_dollar(&cur, &line);
		else if ((*line == '\'' || *line == '"')
				&& (!f || ++(*f)) && mod <= 1)
			line++;
		else if (*line == '`' && (!f || ++(*f))
				&& (mod == 1 || mod == 2) && line++)
			ft_bquote(&cur, &line, 0);
		else
			ft_putchar_mshbuf(&cur, *line++);
	return (ft_buftostr(head));
}

static int	ft_heredoc_toread(t_token *tok)
{
	int		ret;
	char	*line;
	int		f;

	line = NULL;
	f = 0;
	get_term()->heredoc_key = parse_heredoc(tok->data.redir.right, 0, &f);
	while (get_term()->heredoc_key && (ret = ft_readline(0, &line)) > 0)
	{
		if (!ft_strcmp(line, get_term()->heredoc_key))
			break ;
		tok->data.redir.hd = ft_strextend(tok->data.redir.hd, line);
		line = ft_strjoin(tok->data.redir.hd, "\n");
		free(tok->data.redir.hd);
		tok->data.redir.hd = line;
		line = NULL;
	}
	free(line);
	line = tok->data.redir.hd;
	tok->data.redir.hd = parse_heredoc(line, f ? 3 : 2, NULL);
	free(line);
	ft_memdel((void**)&get_term()->heredoc_key);
	ft_is_interrupted();
	return (ret == -1 ? 0 : 1);
}

int			ft_heredoc(t_list *toks)
{
	t_token	*tok;
	int		ret;

	ret = 1;
	get_term()->prompt = P_HEREDOC;
	while (toks)
	{
		tok = toks->content;
		if (tok->type == heredoc || tok->type == heredoc_t)
		{
			if (!(ret = ft_heredoc_toread(tok)))
				break ;
		}
		else if (tok->type == herestr)
			tok->data.redir.hd = parse_heredoc(tok->data.redir.right, 1, NULL);
		toks = toks->next;
	}
	get_term()->prompt = P_USER;
	return (ret);
}
