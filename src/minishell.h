/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:59:09 by marvin            #+#    #+#             */
/*   Updated: 2022/03/09 13:06:13 by dabel-co         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <signal.h>
# include "../libft/src/libft.h"

# define RD_END	0
# define WR_END	1

# define ERR_SYNT_Q "minishell: syntax error near unclosed quotes: "
# define ERR_SYNT_T "minishell: syntax error near unexpected token: `"

int	g_err;

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
	int		zyzz;
}				t_envir;

char	*search_comm(char *comm, char **paths, t_exec *exec);
int		ft_cd(char *path, t_envir *env);
int		ft_pwd(int wfd);
int		ft_echo(char **argv, int wfd);
int		ft_env(char **str, int mode, int wfd);
// int		ft_env(char **env_print, int wfd);
int		ft_unset(t_envir *env, char *str);
// int		ft_unset(t_envir *env, char **argv);
int		ft_export(t_envir *env, char *str, int wfd);
// int		ft_export(t_envir *env, char **argv, int wfd);
int		find_env(char *env, char *str);
void	update_paths(t_envir *env);
//char	*expand(char *str, t_envir *env);
char	**get_env(char **envp);
char	**get_paths(char **envp);
void	update_shlvl(t_envir *env);
char	**check_path(t_envir *env);
char	**init_split(char *str);
char	*expand_line(char *str, t_envir *env, int i, int p);
// char	*expand_line(char *str, t_envir *env);
char	*get_env_value(char *str, t_envir *env);
int		find_env_expand(char *env, char *str);
t_exec	*tokenizator(char **orders, t_envir *env);
char	**smart_split(char *order, char limit);
int		take_all_heredoc(char **comm);
int		take_all_redir(char **order, t_exec *execord);
char	*search_op(char *comm, char search);
int		exec_list(t_exec *list, t_envir *env, int *subp_count);
char	*remove_quotes(char *str);
void	handle_signals(int sig);
void	handle_signals_subprocess(int sig);
void	check_signal_mode(char *str);
char	*take_keyword(char *str, int *end);
int		line_parse(char **line);
void	free_list(t_exec *list);
void	free_node(t_exec *node);
void	free_array(char **array);
char	*err_syntax(char problem);
char	*err_file(char *filename, char *error);
int		is_valid_id(char *str);
char	**env_search(char **env, char *to_search, int name_size);
char	*env_retrieve(char *var, t_envir *env, int free_flag);
int		env_replace(char *str, t_envir *env);
void	env_update(t_envir *env, char **argv, int new_var);
void	env_remove(char *to_remove, t_envir *env, int name_size);
void	env_home_export(char *new_var, t_envir *env, int free_flag);

#endif
