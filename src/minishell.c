/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/02/24 17:58:45 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readfromprompt(t_envir *env)
{
	char	*new_comm;
	int		subp_count;

	new_comm = readline("Newminishell@whodis$ ");
	if (ft_strnstr(new_comm, "exit", 4) && new_comm[4] == '\0')
		exit(0);
	subp_count = exec_list(tokenizator(smart_split(new_comm, '|'), env), env, 0);
	ft_putstr_fd("number of subprocesses: ", 1);
	ft_putnbr_fd(subp_count, 1);
	ft_putchar_fd('\n', 1);
	while (subp_count-- > 0)
		waitpid(-1, NULL, 0);
	add_history(new_comm);
}

static	void	handle_signals(int sig)
{
	if (sig == 2) //CONTROL-C
		exit(0);
	if (sig == 3) //CONTROL-D
		exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_envir	env;
	struct	sigaction sa;

	(void)argc;
	(void)argv;
	sa.sa_handler = &handle_signals;
	sigaction(SIGINT, &sa, NULL); //CONTROL-C
	sigaction(SIGQUIT, &sa, NULL); //CONTROL-D
	env.e_envp = get_env(envp);
	if (!check_path(&env))
		env.paths = get_paths(envp);
	else
		env.paths = check_path(&env);
	update_shlvl(&env);
	while (1)
		readfromprompt(&env);
}
