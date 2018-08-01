#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 20:19:57 by ahrytsen          #+#    #+#              #
#    Updated: 2018/08/01 03:13:31 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 		=	42sh

#===========================================================
OS			= $(shell uname)
ifeq ($(OS),Darwin)
	INC		=	-I./inc/ -I./libft/inc/
	LIBFT	= ./libft/libftprintf.a
	SUB_MAKE= ./libft
	TCAP	= -ltermcap
	CYAN	= \x1b[1;36m
	NON		= \x1b[0m
	CYANN	= \x1b[36m
	GREEN	= \x1b[32m
else
	INC		= -I../../libft_win/includes -I./inc
	LIBFT	= ../../libft_win/libftprintf.a
	SUB_MAKE= ../../libft_win
	TCAP	= -lcurses
endif
#===========================================================


INC_LIB		=	-L./libft -lftprintf $(TCAP)

LIBFT		=	libft/libftprintf.a

DIRSRC		=	./src/

DIROBJ		=	./obj/

HDR			=	inc/twenty_one_sh.h

SRC			=	main.c\
				init.c\
				env_utils.c\
				ft_buffer.c\
				ft_tokenize.c\
				ft_tokenize_utils.c\
				ft_ast.c\
				ft_ast_utils.c\
				ft_ast_exec.c\
				ft_cmdlst.c\
				ft_cmdlst_utils.c\
				ft_cmdlst_exec.c\
				ft_argv.c\
				ft_argv_utils.c\
				ft_argv_quotes.c\
				ft_argv_exec.c\
				ft_redirection.c\
				ft_redirection_utils.c\
				ft_heredoc.c\
				ft_jobs_utils.c\
				\
				builtins/builtins.c\
				builtins/env_builtin.c\
				builtins/ft_cd.c\
				builtins/ft_fg.c\
				\
				ft_readline/ft_autocomplit.c\
				ft_readline/ft_readline.c\
				ft_readline/ft_readline_action.c\
				ft_readline/line.c\
				ft_readline/rl_init.c\
				ft_readline/ft_cursor.c\
				ft_readline/ft_readline_helper.c\
				ft_readline/ft_history.c\
				ft_readline/ft_highlight.c\
				ft_readline/line_edit.c\
				ft_readline/ft_prompt.c\
				ft_readline/ft_check_line.c\
				ft_readline/ft_read.c

OBJ			=	$(addprefix $(DIROBJ), $(SRC:.c=.o))

CC			=	gcc
RM			=	rm -rf
ECHO		=	echo

#===========================================================
ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -g
	endif
else
CFLAGS		= 	-Wall -Wextra -Werror -Ofast -flto=thin
endif
#===========================================================
STRING1 = $(CYAN)---Compile_$(NAME)$(NON)
STRING2 = $(CYAN)---Remove_$(NAME)_O_Files$(NON)
STRING3 = $(CYAN)---Remove_$(NAME)$(NON)
STRING4 = $(CYAN)---Running$(NON)
STRING5 = $(CYAN)---Copy binary file in ~/my_bin$(NON)
STRING5 = $(CYAN)---$(NAME) installed in ~/.my_bin$(NON)
#===========================================================

.PHONY: all clean re

all: $(NAME)

$(NAME): $(LIBFT) $(DIROBJ) $(OBJ)
	@echo "$(STRING1)"
	@$(CC) $(INC) $(INC_LIB) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(CYANN)comp$(NON)..."$(NAME)"...$(GREEN)OK$(NON)"

$(DIROBJ):
	mkdir -p $(DIROBJ)
	mkdir -p $(DIROBJ)/ft_readline
	mkdir -p $(DIROBJ)/builtins

lib:
	@$(MAKE) -C $(SUB_MAKE) -j3

$(LIBFT): lib

$(OBJ):	$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@echo "$(CYANN)comp$(NON)..."$@

clean:
	@($(RM) $(DIROBJ))
ifdef SUB_MAKE
	@$(MAKE) -C $(SUB_MAKE) clean
endif
	@$(ECHO) "$(STRING2)"

fclean: clean
ifdef SUB_MAKE
	@$(MAKE) -C $(SUB_MAKE) fclean
endif
	-@$(RM) $(NAME)
	@echo "$(STRING3)"

re: fclean all

clear:
	@echo "$(STRING2)"
	@rm -rf $(OBJ)
	@echo "$(STRING3)"
	@rm -rf $(NAME)

run:
	@echo "$(STRING4)"
	@./$(NAME)

test:

os:
	@echo "<"$(OS)"> OS it is"

inst:
	@echo "$(STRING5)"
	@cp $(NAME) ~/my_bin

install:
	@echo "$(STRING6)"
	@cp $(NAME) ~/.my_bin

.NOTEPARALLEL: all $(NAME) re
