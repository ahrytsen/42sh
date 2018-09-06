#!/usr/bin/env 42sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 18:40:56 by ahrytsen          #+#    #+#              #
#    Updated: 2018/09/05 21:21:40 by ahrytsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

say -v Milena "Привет, зайка" #feat Milena
echo $1 $2 $3 $4
read < src/main.c
echo $REPLY
{echo,*}
lol=kek
echo $lol
echo $(ls) | wc

