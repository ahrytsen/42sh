#!/usr/bin/env 42sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 18:40:56 by ahrytsen          #+#    #+#              #
#    Updated: 2018/09/13 23:53:02 by ahrytsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

say -v Milena "Привет, зайка! Меня зовут $0" #feat Milena
echo $1 $2 $3 $4
read < src/main.c
echo $REPLY
{echo,*}
lol=kek
echo $lol
echo $(ls) | wc
echo "\n\n=================================================================="
echo "\t\t\tOUR BONUSES:"
echo "=================================================================="
echo "\tcommand substitution ('\`' and '\$()')
\talias and unalias
\tsymbolic links
\tall env flags
\tshell parameters
\t'<>' (open custom descriptor)
\t'<<<' (herestring)
\t'<&, >&, &> and &>>' (file descriptor agregation)
\t'>|' (same as '>' in out implementation)
\t'<<-' (delete all leading tab characters in heredoc lines)
\t~-, ~+, ~*user_name*
\tfield splitting
\t.42shrc
\t.ft_history"
echo "==================================================================\n\n"
echo "=======test '<<-'==========="
cat <<- EOF
		lol kek
		y nas buv segfolt
		lol
		EOF
echo "=======test '<<'==========="
cat << EOF
		lol kek
		y nas buv segfolt
		lol
EOF
echo "=======test 'leaks'==========="
leaks --quiet $$
echo "=========ETO KANEC============"
