/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 13:26:53 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/16 13:28:41 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_free_arr(void **arr)
{
	void **ptr;

	if (arr)
	{
		ptr = arr;
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
		free(arr);
		arr = NULL;
	}
}
