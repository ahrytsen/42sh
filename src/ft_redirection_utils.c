/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 19:39:06 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/06/19 20:32:42 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		ft_redir_right_param(t_token *tok)
{
	int		count_digits;
	char	*tmp;

	tmp = tok->data.redir.right;
	count_digits = 0;
	while (*tmp)
	{
		if (*tmp == '-' && !tmp[1])
			tok->data.redir.cls = 1;
		else if (!ft_isdigit(*tmp))
			return (0);
		else
			count_digits++;
		tmp++;
	}
	tok->data.redir.nbr = count_digits ? ft_atoi(tok->data.redir.right) : -1;
	return (1);
}
