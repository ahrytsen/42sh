# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 12:27:21 by dlinkin           #+#    #+#              #
#    Updated: 2018/05/22 12:27:23 by dlinkin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INC)
SRC_DIR = src
SRC = main.c

SRC_FILES = $(foreach a,$(SRC), $(foreach b,$(SRC_DIR), $b/$a))
OBJ_DIR = obj
OBJ_FILES = $(foreach a,$(SRC:%.c=%.o), $(foreach b,$(OBJ_DIR), $b/$a))

OS = $(shell uname)
ifeq ($(OS),Darwin)
	INC = -I./libft/includes -I./inc
	LIBA = ./libft/libftprintf.a
	LIB_DIR = ./libft
	TCAP = -ltermcap
	CYAN = \x1b[1;36m
	NON = \x1b[0m
	CYANN = \x1b[36m
	GREEN = \x1b[32m
else
	INC = -I../../libft_win/includes -I./inc
	LIBA = ../../libft_win/libftprintf.a
	LIB_DIR = ../../libft_win
	TCAP = -lcurses
endif

BIN = 42sh

STRING1 = $(CYAN)---Compile_$(BIN)$(NON)
STRING2 = $(CYAN)---Remove_$(BIN)_O_Files$(NON)
STRING3 = $(CYAN)---Remove_$(BIN)$(NON)
STRING4 = $(CYAN)---Running$(NON)
STRING5 = $(CYAN)---Copy binary file in ~/my_bin$(NON)

.PHONY: $(LIBA)

all: library $(OBJ_DIR) $(BIN)

$(BIN): $(OBJ_FILES)
	@echo "$(STRING1)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBA) $(TCAP) -o $(BIN)
	@echo "$(CYANN)comp$(NON)..."$(BIN)"...$(GREEN)OK$(NON)"

library: $(LIBA)
	@make -C $(LIB_DIR) -j3

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(CYANN)comp$(NON)..."$@

clean:
	@echo "$(STRING2)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)

fclean: clean
	@echo "$(STRING3)"
	@rm -rf $(BIN)
	@make clean_lib -C $(LIB_DIR)

clear:
	@echo "$(STRING2)"
	@rm -rf $(OBJ)
	@echo "$(STRING3)"
	@rm -rf $(BIN)

re: fclean all

run:
	@echo "$(STRING4)"
	@./$(BIN)

test:

os:
	@echo "<"$(OS)"> OS it is"

inst:
	@echo "$(STRING5)"
	@cp $(BIN) ~/my_bin
