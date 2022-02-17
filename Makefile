# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/02 20:21:22 by dabel-co          #+#    #+#              #
#    Updated: 2022/02/14 11:19:25 by dabel-co         ###   ########.fr        #
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
		ord_split \
		unset \
		env \
		export \
		input_redir \
		output_redir \
		exec_line \
		split_line \
		expand_line

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
