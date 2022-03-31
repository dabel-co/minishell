/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/03/09 12:04:20 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**check_path(t_envir *env)
// {
// 	int		i;
// 	char	*aux;

// 	i = 0;
// 	aux = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:";
// 	while (find_env(env->e_envp[i], "PATH=") && env->e_envp[i] != NULL)
// 		i++;
// 	if (env->e_envp[i] == NULL)
// 		return (get_paths(&aux));
// 	return (NULL);
// }

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

char	**update_paths(t_envir *env)
{
	char	*paths;
	char	**ret;

	if (env->paths)
		free_array(env->paths);
	paths = env_retrieve("PATH", env, 0);
	if (!paths)
		return (NULL);
	ret = ft_split(paths, ':');
	free(paths);
	return (ret);
}

int	is_all_num(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

void	update_shlvl(t_envir *env)
{
	char	*number;
	int		shlvl;

	number = env_retrieve("SHLVL", env, 0);
	if (!number || !is_all_num(number))
	{
		home_export("SHLVL=1", env, 0);
		return ;
	}
	shlvl = ft_atoi(number) + 1;
	if (shlvl >= 1000 || shlvl < 0)
		shlvl = 1;
	free(number);
	number = ft_itoa(shlvl);
	home_export(ft_strjoin("SHLVL=", number), env, 1);
	free(number);
}
