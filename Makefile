# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/02 20:21:22 by dabel-co          #+#    #+#              #
#    Updated: 2022/03/09 12:44:01 by dabel-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address
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
		remove_quotes \
		signals \
		take_keyword \
		line_parse \
		free_func \
		err_func

C = $(addprefix ./src/, $(addsuffix .c, $(FILES)))
all: $(NAME)

$(NAME) :	check_libft
	$(CC) -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(FLAGS) $(C) $(READLINE) -o $(NAME) ./libft/libft.a
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
