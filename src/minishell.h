/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:59:09 by marvin            #+#    #+#             */
/*   Updated: 2022/02/10 12:20:47 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/src/libft.h"
# include <errno.h>

# define RD_END	0
# define WR_END	1

typedef struct s_execord
{
	char	*comm;
	char	**argsum;
	char	free;
	int		in_fd;
	char	ignore;
	//adding my things
	char	**eof;
}				t_execord;

typedef struct s_envir
{
	char	**paths;
	char	**e_envp;
}				t_envir;

void	exec_comm(char *comm, t_envir *env);
char	*search_comm(char *comm, char **paths);
int		ft_cd(char *path, t_envir *env);
int		ft_pwd(void);
int		ft_echo(char **argv);
char	**ord_split(char *comm_line);
void	exec_line(char *comm_line, t_envir *env);
int		ft_env(char **str, int mode);
void	ft_unset(t_envir *env, char *str);
void	ft_export(t_envir *env, char *str);
int		find_env(char *env, char *str);
void	update_paths(t_envir *env);
char	*expand(char *str, t_envir *env);
int		input_redir(char **comm, int rfd, t_envir *env);
int		output_redir(char **comm, int wfd);
void	exec_line(char *comm_line, t_envir *env);
void	exec(t_execord *execorder, t_envir *env);
//int 	ft_strcmp(char *str1, char *str2);
char	**get_env(char **envp);
char	**get_paths(char **envp);
void	update_shlvl(t_envir *env);
char	**check_path(t_envir *env);
char	**init_split(char *str);
#endif
