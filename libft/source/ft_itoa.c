/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:30:13 by dlinkin           #+#    #+#             */
/*   Updated: 2017/10/31 16:30:14 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ahoi(char *str, int n, int i)
{
	if (n < 10 && n > -10)
		if (n < 0)
		{
			str[i] = n * -1 + 48;
			str[i - 1] = '-';
		}
		else
		{
			str[i] = n + 48;
		}
	else
	{
		if (n > 9)
			str[i] = n % 10 + 48;
		else
			str[i] = (n % 10) * -1 + 48;
		ft_ahoi(str, n / 10, i - 1);
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		cp;

	len = 0;
	cp = n;
	while (cp > 9 || cp < -9)
	{
		cp /= 10;
		len++;
	}
	if (cp >= 0)
		len++;
	else
		len += 2;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_ahoi(str, n, len - 1);
	str[len] = '\0';
	return (str);
}
