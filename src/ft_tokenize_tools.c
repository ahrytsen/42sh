/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 20:36:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/13 21:03:53 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_token_del(void *token, size_t size)
{
	(void)size;
	if (((t_token*)token)->type >= heredoc
		&& ((t_token*)token)->type <= herestr)
		free(((t_token*)token)->data.redir.hd);
	free(token);
}

int		ft_isseparator(int c)
{
	return (ft_strchr("|&;()<> \t\n", c) ? 1 : 0);
}
