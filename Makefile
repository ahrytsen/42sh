#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/03 20:19:57 by ahrytsen          #+#    #+#              #
#    Updated: 2018/09/13 23:54:48 by ahrytsen         ###   ########.fr        #
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

DIRSRC		=	./src/

DIROBJ		=	./obj/

HDR			=	inc/ft_sh.h\
				inc/ft_readline.h\
				inc/ft_expansions.h

SRC			=	ft_argv.c\
				ft_argv_exec.c\
				ft_ast.c\
				ft_ast_exec.c\
				ft_ast_debug.c\
				ft_ast_utils.c\
				ft_alias_checker.c\
				ft_buffer.c\
				ft_buffer_spec.c\
				ft_cmd_print.c\
				ft_cmdlst.c\
				ft_cmdlst_utils.c\
				ft_cmdlst_exec.c\
				ft_heredoc.c\
				ft_init.c\
				ft_jobs_utils.c\
				ft_jobs_helper.c\
				ft_shell_var.c\
				ft_shell_var_init.c\
				ft_shell_var_toolz.c\
				ft_shell_var_utils.c\
				ft_redirection.c\
				ft_redirection_utils.c\
				ft_tokenize.c\
				ft_tokenize_tools.c\
				ft_tokenize_utils.c\
				main.c\
				\
				ft_builtins/ft_builtins.c\
				ft_builtins/ft_bi_alias.c\
				ft_builtins/ft_bi_unalias.c\
				ft_builtins/ft_bi_bg.c\
				ft_builtins/ft_bi_cd.c\
				ft_builtins/ft_bi_env.c\
				ft_builtins/ft_bi_export.c\
				ft_builtins/ft_bi_fg.c\
				ft_builtins/ft_bi_jobs.c\
				ft_builtins/ft_bi_jobs_tools.c\
				ft_builtins/ft_bi_history.c\
				ft_builtins/ft_bi_history_toolz.c\
				ft_builtins/ft_bi_history_utils.c\
				ft_builtins/ft_bi_un_set.c\
				ft_builtins/ft_bi_un_setenv.c\
				ft_builtins/ft_bi_read.c\
				ft_builtins/ft_bi_read_records.c\
				ft_builtins/ft_bi_read_get_last_var.c\
				\
				ft_readline/ft_readline.c\
				ft_readline/ft_rl_autocomplit.c\
				ft_readline/ft_rl_autocomp_cmd_and_var.c\
				ft_readline/ft_rl_autocomp_drawer.c\
				ft_readline/ft_rl_autocomp_filenames.c\
				ft_readline/ft_rl_action.c\
				ft_readline/ft_rl_init.c\
				ft_readline/ft_rl_check_line.c\
				ft_readline/ft_rl_cursor.c\
				ft_readline/ft_rl_exclamation.c\
				ft_readline/ft_rl_helper.c\
				ft_readline/ft_rl_history.c\
				ft_readline/ft_rl_highlight.c\
				ft_readline/ft_rl_line_edit.c\
				ft_readline/ft_rl_line.c\
				ft_readline/ft_rl_prompt.c\
				ft_readline/ft_rl_read.c\
				\
				ft_expansions/brace/auxiliary_funcs.c\
				ft_expansions/brace/expand_braces.c\
				ft_expansions/brace/fill_buf.c\
				ft_expansions/brace/get_range.c\
				ft_expansions/brace/get_seq.c\
				\
				ft_expansions/pathname/brackets.c\
				ft_expansions/pathname/regex.c\
				ft_expansions/pathname/check_brackets.c\
				ft_expansions/pathname/ft_strcut.c\
				\
				ft_expansions/tilde_var_cmd/tilde.c\
				ft_expansions/tilde_var_cmd/substitute_variable.c\
				ft_expansions/tilde_var_cmd/substitute_cmd.c\
				ft_expansions/tilde_var_cmd/tools.c\
				\
				ft_expansions/quote/quote_removal.c\
				ft_expansions/quote/bslash_removal.c\
		        ft_expansions/field/field_splitting.c

OBJ			=	$(addprefix $(DIROBJ), $(SRC:.c=.o))

CC			=	clang
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
CFLAGS		= 	-Wall -Wextra -Werror -O2 -flto=thin
endif
#===========================================================
STRING1 = $(CYAN)---Compile_$(NAME)$(NON)
STRING2 = $(CYAN)---Remove_$(NAME)_O_Files$(NON)
STRING3 = $(CYAN)---Remove_$(NAME)$(NON)
STRING4 = $(CYAN)---Running$(NON)
STRING5 = $(CYAN)---Copy binary file in ~/my_bin$(NON)
STRING6 = $(CYAN)---$(NAME) installed in ~/.mybin$(NON)
#===========================================================

.PHONY: all clean re

all: lib $(NAME)

$(NAME): $(LIBFT) $(DIROBJ) $(OBJ)
	@echo "$(STRING1)"
	@$(CC) $(INC) $(INC_LIB) $(CFLAGS) $(OBJ) -o $(NAME) libft/libftprintf.a
	@echo "$(CYANN)comp$(NON)..."$(NAME)"...$(GREEN)OK$(NON)"

$(DIROBJ):
	mkdir -p $(DIROBJ)
	mkdir -p $(DIROBJ)ft_readline
	mkdir -p $(DIROBJ)ft_builtins
	mkdir -p $(DIROBJ)ft_expansions
	mkdir -p $(DIROBJ)ft_expansions/brace
	mkdir -p $(DIROBJ)ft_expansions/pathname
	mkdir -p $(DIROBJ)ft_expansions/tilde_var_cmd
	mkdir -p $(DIROBJ)ft_expansions/quote
	mkdir -p $(DIROBJ)ft_expansions/field

$(LIBFT): lib

lib:
	@$(MAKE) -C $(SUB_MAKE) -j3

$(OBJ):	$(DIROBJ)%.o : $(DIRSRC)%.c $(HDR)
	@$(CC) $(INC) $(CFLAGS) -o $@ -c $<
	@echo "$(CYANN)comp$(NON)..."$@

clean:
	@$(RM) $(DIROBJ)
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
	@rm -rf $(DIROBJ)
	@echo "$(STRING3)"
	@rm -rf $(NAME)

run:
	@echo "$(STRING4)"
	./$(NAME)

test:

os:
	@echo "<"$(OS)"> OS it is"

inst:
	@echo "$(STRING5)"
	@cp $(NAME) ~/my_bin

install:
	@echo "$(STRING6)"
	@mkdir -p $(HOME)/.mybin/
	@cp $(NAME) $(HOME)/.mybin/

.NOTEPARALLEL: all $(NAME) re

dbg:
	@./42sh 2>file
