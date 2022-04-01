# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/02 20:21:22 by dabel-co          #+#    #+#              #
#    Updated: 2022/04/01 19:00:07 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = cc
LIBFT = ./libft/libft.a
READLINE = -lreadline
CFILES =	minishell \
		init_shell \
		search_comm \
		pwd \
		cd \
		echo \
		export \
		expand_line \
		exec_list \
		search_op \
		smart_split \
		take_all_heredoc \
		take_all_redir \
		tokenizator \
		remove_quotes \
		signals \
		take_keyword \
		line_parse \
		free_func \
		err_file \
		env \
		m_exit \
		env_func \
		unset \
		home_export \
		is_valid_id

SRC = $(addprefix ./src/, $(addsuffix .c, $(CFILES)))

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	@echo -n "compiling minishell: "
	@$(CC) -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(FLAGS) $(SRC) $(READLINE) -o $(NAME) $(LIBFT)
	@echo "\e[0;32mminishell compiled\e[0;0m"
	
$(LIBFT):
	@if test -d libft; then ( cd libft ; git pull ) ; else git clone -q https://github.com/dabel-co/libft.git; fi
	@echo -n "compiling libft: "
	@make extra --no-print-directory -C ./libft
	@echo "\e[0;32mlibft compiled\e[0;0m"
	
clean:
	rm -f $(NAME)
	rm -rf minishell.dSYM 
	
fclean: clean
	make fclean -C ./libft
	
g : fclean
	rm -rf ./libft

re: clean all

.PHONY : all clean fclean re
