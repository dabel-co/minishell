/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/04/07 13:04:16 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(char *comm, t_envir *env)
{
	char **args;

	if (search_op(comm, '|'))
		return (0);
	args = smart_split(ft_strdup(comm), ' ');
	if (!ft_strcmp(args[0], "exit"))
		return (0);
	if (!args[1])
		return (1);
	if (!is_all_num(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
		env->zyzz = 255;
		return (1);
	}
	if (!args[2])
	{
		env->zyzz = ft_atoi(args[1]);
		return (1);
	}
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (0);
}

void	readfromprompt(t_envir *env)
{
	char	*new_comm;

	new_comm = readline(env->prompt);
	if (!new_comm || check_exit(new_comm, env))
	{
		free(new_comm);
		rl_clear_history();
		ft_putstr_fd("exit\n", 1);
		m_exit(env);
	}
	g_err = 0;
	if (line_parse(&new_comm))
		exec_list(tokenizator(smart_split(new_comm, '|'), env), env, 0);
	if (new_comm[0])
		add_history(new_comm);
	free(new_comm);
}

void	readfromfile(t_envir *env)
{
	int		nbytes;
	char	*new_comm;

	ioctl(STDIN_FILENO, FIONREAD, &nbytes);
	while (nbytes)
	{
		new_comm = readline(env->prompt);
		if (ft_strcmp(new_comm, "exit"))
		{
			free(new_comm);
			m_exit(env);
		}
		if (line_parse(&new_comm))
		{
			g_err = 0;
			exec_list(tokenizator(smart_split(new_comm, '|'), env), env, 0);
		}
		free(new_comm);
		ioctl(STDIN_FILENO, FIONREAD, &nbytes);
	}
}

char	*get_prompt(t_envir *env)
{
	char	*user;

	user = env_retrieve("USER", env, 0);
	if (!user)
		user = ft_strdup("ghost");
	return (ft_strjoin_free(user, "@minishell$ "));
}

int	main(int argc, char **argv, char **envp)
{
	t_envir	env;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	env.e_envp = get_env(envp);
	env.paths = update_paths(&env);
	env.prompt = get_prompt(&env);
	if (!env.paths)
		env.paths = ft_split(AUX_PATH, ':');
	update_shlvl(&env);
	if (isatty(STDIN_FILENO))
		while (1)
			readfromprompt(&env);
	else
		readfromfile(&env);
}
