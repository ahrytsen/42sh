# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/26 13:13:13 by dlinkin           #+#    #+#              #
#    Updated: 2018/07/31 21:00:14 by ahrytsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

INC = ./includes

CFLAGS = -Wall -Wextra -Werror -I$(INC)

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
