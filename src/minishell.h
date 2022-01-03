/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:59:09 by marvin            #+#    #+#             */
/*   Updated: 2022/01/03 13:31:09 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/src/libft.h"

typedef struct s_execord
{
	char	*comm;
	char	**argsum;
	char	free;
}				t_execord;

typedef struct s_envir
{
	char	**paths;
	char	**envp;
}				t_envir;

void	exec_comm(char *comm, t_envir *env);
char	*search_comm(char *comm, char **paths);
int		ft_cd(char *path);
int 	*ft_pwd(void);
int		ft_echo(char **argv);

#endif
