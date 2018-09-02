/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 21:00:10 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/09/01 14:51:13 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ft_readline.h"
#include "ft_expansions.h"

static char	*parse_key(char *key, int *f)
{
	t_list tmp;

	f ? (*f = 0) : 0;
	tmp.content = ft_strdup(key);
	remove_quotes(&tmp);
	if (f && ft_strcmp(key, tmp.content))
		*f = 1;
	return (tmp.content);
}

char		*ft_heredoc_expansion(char *s)
{
	char	*tmp;
	t_buf	*head;
	t_buf	*cur;

	tmp = s;
	if (!s || !(head = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	cur = head;
	while (*s)
		if (*s == '\\' && s++)
		{
			if (*s != '$' && *s != '`' && *s != '\\')
				ft_putchar_mshbuf(&cur, '\\');
			ft_putchar_mshbuf(&cur, *s++);
		}
	/*else if (*s == '`' && s++)
	  ft_bquote(&cur, &s, 0);
		else if (*s == '$' && *(s + 1) == '(' && (s += 2))
		ft_bquote(&cur, &s, 0);*/
		else if (*s == '$' && s++)
			s = record_var(&cur, s);
		else
			ft_putchar_mshbuf(&cur, *s++);
	return (ft_buftostr(head));
}

static int	ft_heredoc_toread(t_token *tok)
{
	int		ret;
	char	*line;
	char	*tmp;
	int		i;

	ret = 0;
	line = NULL;
	get_term()->heredoc_key = parse_key(tok->word, &tok->data.redir.nbr);
	while (get_term()->heredoc_key && (ret = ft_readline(0, &line)) > 0
			&& ft_strcmp(line, get_term()->heredoc_key) && !(i = 0))
	{
		while (tok->data.redir.type == heredoc_t && line[i] == '\t')
			i++;
		tmp = tok->data.redir.hd;
		ft_asprintf(&tok->data.redir.hd, "%s%s\n", tmp ? tmp : "", line + i);
		free(tmp);
		ft_memdel((void**)&line);
	}
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
		if (tok->type == redir && (tok->data.redir.type == heredoc
		|| tok->data.redir.type == heredoc_t)
		&& !(ret = ft_heredoc_toread(tok)))
			break ;
		else if (tok->type == redir && tok->data.redir.type == herestr)
			tok->data.redir.hd = tok->word;
		toks = toks->next;
	}
	get_term()->prompt = P_USER;
	return (ret);
}
