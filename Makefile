# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/02 20:21:22 by dabel-co          #+#    #+#              #
#    Updated: 2022/02/24 17:23:47 by vguttenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
CC = cc
READLINE = -lreadline
FILES =	minishell \
		init_shell \
		search_comm \
		pwd \
		cd \
		echo \
		unset \
		env \
		export \
		expand_line \
		exec_list \
		search_op \
		smart_split \
		take_all_heredoc \
		take_all_redir \
		tokenizator \
		remove_quotes

C = $(addprefix ./src/, $(addsuffix .c, $(FILES)))
all: $(NAME)

$(NAME) :	check_libft
	$(CC) $(FLAGS) $(C) -o $(NAME) $(READLINE) ./libft/libft.a
check_libft :
	@if test -d libft; then ( cd libft ; git pull ) ; else git clone https://github.com/dabel-co/libft.git; fi
	@make extra -C ./libft
clean:
	rm -f $(NAME)
	rm -rf minishell.dSYM
fclean: clean
	make fclean -C ./libft
g : fclean
	rm -rf ./libft
re: clean all

.PHONY : all clean fclean re check_libft
