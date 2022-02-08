/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/02/07 13:41:52 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readfromprompt(t_envir *env)
{
	char	*new_comm;

	new_comm = readline("Newminishell@whodis$ ");
	if (ft_strnstr(new_comm, "exit", 4) && new_comm[4] == '\0')
		exit(0);
	exec_line(new_comm, env);
	add_history(new_comm);
}

int	main(int argc, char **argv, char **envp)
{
	t_envir	env;

	(void)argc;
	(void)argv;
	env.e_envp = get_env(envp);
	if (!check_path(&env))
		env.paths = get_paths(envp);
	else
		env.paths = check_path(&env);
	update_shlvl(&env);
	while (1)
		readfromprompt(&env);
}
