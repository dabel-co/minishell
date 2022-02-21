/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 20:12:00 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/21 18:20:51 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATOR_H
# define TOKENIZATOR_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

# define RD_END 0
# define WR_END 1

typedef struct s_exec
{
    char            *exec_path;
    char            **argv;
    int             in_fd;
    int             out_fd;
    char            *err_msg;
    struct s_exec   *next;
}               t_exec;

int 	take_all_heredoc(char **comm);
int 	take_all_redir(char **order, t_exec *execord);
char    **smart_split(char *order, char limit);
char    *ft_strcrop_free(char *str, unsigned int start, size_t len);
char    *ft_strjoin_free(char *keeper, char *buffer);

#endif
