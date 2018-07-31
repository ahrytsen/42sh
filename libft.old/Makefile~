# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/26 13:13:13 by dlinkin           #+#    #+#              #
#    Updated: 2018/05/09 18:37:30 by dlinkin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libftprintf.a
INC = ./includes
CFLAGS = -Wall -Wextra -Werror -I$(INC)
SRC =	ft_atoi.c\
		ft_bzero.c\
		ft_is_blank.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isnumber.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_free_arr.c\
		ft_lstadd.c\
		ft_lstdel.c\
		ft_lstdelone.c\
		ft_lstfree.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_lstprint.c\
		ft_lstpushback.c\
		ft_lstsize.c\
		ft_lstsort.c\
		ft_memalloc.c\
		ft_memccpy.c\
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
		ft_strcat.c\
		ft_strchr.c\
		ft_strclr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strequ.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlen.c\
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
		ft_tolower.c\
		ft_toupper.c\
		ft_itoa_base.c\
		ft_printf.c\
		ft_dprintf.c\
		printf_tools/ft_tp_lenth.c\
		printf_tools/ft_tp_put.c\
		printf_tools/ft_tp_set.c\
		printf_tools/ft_tp_chars.c\
		printf_tools/ft_tp_unsigned.c\
		printf_tools/ft_tp_signed.c\
		printf_tools/ft_tp_science.c\
		printf_tools/ft_tp_sci_exp.c\
		printf_tools/ft_tp_sci_flo.c\
		printf_tools/ft_tp_print_binry.c\
		printf_tools/ft_tp_non_printable.c\
		printf_tools/ft_tp_date.c\
		get_next_line.c
SRC_DIR = source
SRC_FILES = $(foreach a,$(SRC), $(foreach b,$(SRC_DIR), $b/$a))
OBJ_DIR = object
OBJ_FILES = $(foreach a,$(SRC:%.c=%.o), $(foreach b,$(OBJ_DIR), $b/$a))
HED =	includes/libft.h\
		includes/libftprintf.h

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

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(STRING1)"
	@ar rc $(NAME) $(OBJ_FILES)
	@ranlib $(NAME)
	@echo "$(BBLUE)comp$(NON)..."$(NAME)"...$(GRN)OK$(NON)\n"

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	mkdir $(OBJ_DIR)/printf_tools

$(OBJ_DIR)/get_next_line.o: $(SRC_DIR)/get_next_line.c $(HED)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(BLUE)comp$(NON)..."$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HED)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(BLUE)comp$(NON)..."$@

clean:
	@echo "$(STRING2)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(STRING3)"
	@rm -rf $(NAME)

clean_lib:
	@echo "$(STRING3)"
	@rm -rf $(NAME)

re: fclean all

echo:
	@echo $(SRC_FILES)
