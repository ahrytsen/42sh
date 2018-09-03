/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:30:01 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/08/30 22:24:46 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric_n(char *str, size_t len)
{
	if (!str || !*str)
		return (0);
	while (*str && len--)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}
