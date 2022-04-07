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

void	readfromprompt(t_envir *env)
{
	char	*new_comm;

	new_comm = readline(env->prompt);
	if (!new_comm || ft_strcmp(new_comm, "exit"))
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
