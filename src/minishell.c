/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/01/28 15:03:52 by dabel-co         ###   ########.fr       */
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

static char	**get_env(char **envp)
{
	char	**env;
	int		i;
	int		p;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		p = 0;
		env[i] = (char *)malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		while (envp[i][p] != '\0')
		{
			env[i][p] = envp[i][p];
			p++;
		}
		env[i][p] = '\0';
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*paths;
	char	**result;

	i = 0;
	while (envp[i])
	{
		paths = ft_strnstr(envp[i], "PATH=", 5);
		if (paths)
			return (ft_split(paths + sizeof(char) * 5, ':'));
		i++;
	}
	result = (char **)malloc(sizeof(char *) * 2);
	result[0] = (char *)malloc(sizeof(char));
	result[0][1] = '\0';
	result[1] = NULL;
	return (result);
}

static void update_shlvl(t_envir *env)
{
	int	shlvl;
	int	i;
	char *x;
	char *aux;

	i = 0;
	shlvl = 0;
	while (find_env(env->e_envp[i], "SHLVL="))
		i++;
	while (env->e_envp[i][shlvl] != '=')
		shlvl++;
	shlvl = ft_atoi(&env->e_envp[i][++shlvl]);
	shlvl++;
	x = ft_itoa(shlvl);
	aux = ft_strjoin("SHLVL=", x);
	ft_export(env, aux);
	free(x);
	free(aux);
}



int	main(int argc, char **argv, char **envp)
{
	t_envir	env;

	(void)argc;
	(void)argv;
	env.paths = get_paths(envp);
	env.e_envp = get_env(envp);
	update_shlvl(&env);
	while (1)
		readfromprompt(&env);
}
