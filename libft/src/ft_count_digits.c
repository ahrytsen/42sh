/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvyliehz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:34:47 by yvyliehz          #+#    #+#             */
/*   Updated: 2018/07/19 12:34:47 by yvyliehz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_digits(ssize_t n)
{
	size_t	digits;

	digits = 1;
	n = ft_absolute(n);
	while (n /= 10)
		digits++;
	return (digits);
}
