#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 20:19:57 by ahrytsen          #+#    #+#              #
#    Updated: 2018/09/03 15:13:58 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	=	libftprintf.a

INC		=	./inc/

DIRSRC	=	./src/

DIROBJ	=	./obj/

HDR		=	inc/libft.h\
			inc/ft_printf.h

SRC		=	ft_absolute.c\
			ft_arrstr.c\
			ft_atoi.c\
			ft_atoi_base.c\
			ft_atol.c\
			ft_atol_base.c\
			ft_bzero.c\
			ft_count_digits.c\
			ft_dtoa.c\
			ft_dtoea.c\
			ft_free_arr.c\
			ft_is_blank.c\
			ft_isalnum.c\
			ft_isalnum_str.c\
			ft_isalpha.c\
			ft_isalpha_str.c\
			ft_isascii.c\
			ft_isascii_str.c\
			ft_isdigit.c\
			ft_isnumber.c\
			ft_isnumeric.c\
			ft_isnumeric_n.c\
			ft_isprint.c\
			ft_isprint_str.c\
			ft_isvar.c\
			ft_iswhitespace.c\
			ft_itoa.c\
			ft_itoa_base.c\
			ft_ldtoa.c\
			ft_ldtoea.c\
			ft_lstadd.c\
			ft_lstadd_end.c\
			ft_lstdel.c\
			ft_lstdelone.c\
			ft_lstfree.c\
			ft_lstiter.c\
			ft_lstmap.c\
			ft_lstnew.c\
			ft_lstprint.c\
			ft_lstpush_back.c\
			ft_lstpush_front.c\
			ft_lstsize.c\
			ft_lstsort.c\
			ft_lstsplit.c\
			ft_ltoa.c\
			ft_memalloc.c\
			ft_memccpy.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memdel.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar.c\
			ft_putchar_fd.c\
			ft_putendl.c\
			ft_putendl_fd.c\
			ft_putnbr.c\
			ft_putnbr_fd.c\
			ft_putstr.c\
			ft_putstr_fd.c\
			ft_realloc.c\
			ft_sort_params.c\
			ft_strarr_free.c\
			ft_strcat.c\
			ft_strchr.c\
			ft_strclr.c\
			ft_strcmp.c\
			ft_strcpy.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strdup_arr.c\
			ft_strequ.c\
			ft_strextend.c\
			ft_strhalfextend.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlen.c\
			ft_strlen_c.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_strncat.c\
			ft_strncmp.c\
			ft_strncpy.c\
			ft_strnequ.c\
			ft_strnew.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strsplit.c\
			ft_strstr.c\
			ft_strsub.c\
			ft_strtrim.c\
			ft_strulen.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_ultoa_base.c\
			ft_wcharlen.c\
			get_next_line.c\
			ft_lstadd_list.c\
			ft_isblank.c\
			ft_iscntrl.c\
			ft_isgraph.c\
			ft_islower.c\
			ft_ispunct.c\
			ft_isupper.c\
			ft_isword.c\
			ft_isxdigit.c\
			ft_strnchr.c\
			ft_lstinsert.c\
			ft_printf/ft_pbuf.c\
			ft_printf/ft_pfloat.c\
			ft_printf/ft_phelper.c\
			ft_printf/ft_phendler.c\
			ft_printf/ft_printf.c\
			ft_printf/ft_asprintf.c\
			ft_printf/ft_pbuf_str.c

OBJ		= $(addprefix $(DIROBJ), $(SRC:.c=.o))

CC		= clang

#===========================================================
ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -g
	endif
else
CFLAGS		= 	-Wall -Wextra -Werror -O2
endif
#===========================================================
OS = $(shell uname)
ifeq ($(OS),Darwin)
	BBLUE = \x1b[1;34m
	NON = \x1b[0m
	BLUE = \x1b[34m
	GRN = \x1b[32m
endif
STRING1 = $(BBLUE)---Compile_Library$(NON)
STRING2 = $(BBLUE)---Remove_Library_O_Files$(NON)
STRING3 = $(BBLUE)---Remove_Library$(NON)
#===========================================================

all: $(NAME)

$(NAME): $(DIROBJ) $(OBJ)
				@echo "$(STRING1)"
				@ar rc $(NAME) $(OBJ);
				@ranlib $(NAME);
				@echo "$(BBLUE)comp$(NON)..."$(NAME)"...$(GRN)OK$(NON)\n"

$(OBJ)	:		$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
				@$(CC) -I$(INC) $(CFLAGS) -o $@ -c $<
				@echo "$(BLUE)comp$(NON)..."$@

clean:
				@rm -rf $(DIROBJ)
				@echo "$(STRING2)"

fclean: clean
				@rm -f $(NAME)
				@echo "$(STRING3)"

clean_lib:
				@echo "$(STRING3)"
				@rm -rf $(NAME)

re: fclean all

$(DIROBJ):
				mkdir -p $(DIROBJ)
				mkdir -p $(DIROBJ)ft_printf

.NOTEPARALLEL: all $(NAME) re
