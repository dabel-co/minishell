/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:59:09 by marvin            #+#    #+#             */
/*   Updated: 2022/02/27 19:37:31 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <signal.h>
# include "../libft/src/libft.h"

# define RD_END	0
# define WR_END	1

typedef struct s_exec
{
	char			*exec_path;
	char			**argv;
	int				in_fd;
	int				out_fd;
	char			*err_msg;
	struct s_exec	*next;
}				t_exec;

typedef struct s_envir
{
	char	**paths;
	char	**e_envp;
}				t_envir;

char	*search_comm(char *comm, char **paths, t_exec *exec);
int		ft_cd(char *path, t_envir *env);
int		ft_pwd(void);
int		ft_echo(char **argv);
int		ft_env(char **str, int mode);
void	ft_unset(t_envir *env, char *str);
void	ft_export(t_envir *env, char *str);
int		find_env(char *env, char *str);
void	update_paths(t_envir *env);
//char	*expand(char *str, t_envir *env);
char	**get_env(char **envp);
char	**get_paths(char **envp);
void	update_shlvl(t_envir *env);
char	**check_path(t_envir *env);
char	**init_split(char *str);
char	*expand_line(char *str, t_envir *env, int i, int p);
char	*env_expand_aux(char *str, t_envir *env);
int		find_env_expand(char *env, char *str);
t_exec	*tokenizator(char **orders, t_envir *env);
char	**smart_split(char *order, char limit);
int		take_all_heredoc(char **comm);
int		take_all_redir(char **order, t_exec *execord);
char	*search_op(char *comm, char search);
int		exec_list(t_exec *list, t_envir *env, int subp_count);
char	*remove_quotes(char *str);
void	handle_signals(int sig);
void	handle_signals_subprocess(int sig);
#endif
