# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/02 20:21:22 by dabel-co          #+#    #+#              #
#    Updated: 2022/01/18 14:51:13 by dabel-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
CC = cc
READLINE = -lreadline
FILES =	minishell \
		exec_comm \
		search_comm \
		pwd \
		cd \
		echo \
		ord_split \
		exec_line \
		unset \
		env \
		export \

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
