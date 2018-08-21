/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 14:33:48 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/21 16:20:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

//static
static void ft_bg_job(t_job *job)
{
	(void)job;
}

int			ft_bg(char **av)
{
	ft_bg_job(NULL);
	if (!*av)
	{

	}
	else
		while (*av)
			;
	return (1);
}
