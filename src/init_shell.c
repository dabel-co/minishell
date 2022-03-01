/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/02/28 16:43:45 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_path(t_envir *env)
{
	int		i;
	char	*aux;

	i = 0;
	aux = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:";
	while (find_env(env->e_envp[i], "PATH=") && env->e_envp[i] != NULL)
		i++;
	if (env->e_envp[i] == NULL)
		return (get_paths(&aux));
	return (NULL);
}

char	**get_env(char **envp)
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
	result[0][0] = '\0';
	result[1] = NULL;
	return (result);
}

void	update_shlvl(t_envir *env)
{
	char	*number;
	int		shlvl;
	char	*aux;
	int		i;

	i = 0;
	shlvl = 0;
	while (find_env(env->e_envp[i], "SHLVL=") && env->e_envp[i] != NULL)
		i++;
	if (env->e_envp[i] == NULL)
	{
		ft_export(env, "SHLVL=1");
		return ;
	}
	while (env->e_envp[i][shlvl] != '=')
		shlvl++;
	shlvl = ft_atoi(&env->e_envp[i][++shlvl]);
	shlvl++;
	if (shlvl >= 1000)
		shlvl = 1;
	number = ft_itoa(shlvl);
	aux = ft_strjoin("SHLVL=", number);
	ft_export(env, aux);
	free(number);
	free(aux);
}
