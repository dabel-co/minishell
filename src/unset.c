/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:37:52 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/09 12:04:05 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*new_env_aux(char *env)
{
	int		p;
	char	*aux;

	aux = env;
	p = 0;
	aux = (char *)malloc((ft_strlen(env) + 1) * sizeof(char));
	while (env[p] != '\0')
	{
		aux[p] = env[p];
		p++;
	}
	aux[p] = '\0';
	return (aux);
}

static char	**new_env(char **env, int size, char *str)
{
	int		i;
	int		s;
	char	**aux;

	i = 0;
	s = 0;
	aux = (char **)malloc((size) * sizeof(char *));
	while (env[s])
	{
		if (!find_env(env[s], str))
			s++;
		if (env[s])
			aux[i] = new_env_aux(env[s]);
		else
			break ;
		i++;
		s++;
	}
	aux[i] = NULL;
	return (aux);
}

void	ft_unset(t_envir *env, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	while (find_env(env->e_envp[i], str) && env->e_envp[i] != NULL)
		i++;
	if (env->e_envp[i] == NULL)
		return ;
	aux = new_env(env->e_envp, ft_env(env->e_envp, 1, 0), str);
	i = 0;
	while (env->e_envp[i])
	{
		free(env->e_envp[i]);
		i++;
	}
	free(env->e_envp);
	env->e_envp = aux;
	if (ft_strncmp("PATH=", str, 5))
		update_paths(env);
}
