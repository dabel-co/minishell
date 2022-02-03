/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/03 12:12:30 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_paths(t_envir *env)
{
	int	i;

	i = 0;
	while (env->paths[i])
	{
		free(env->paths[i]);
		i++;
	}
	free(env->paths[i]);
	env->paths = get_paths(env->e_envp);
}

int	find_env(char *env, char *str)
{
	int	i;

	i = 0;
	if (!env || !str || env == NULL)
		return (-1);
	while (env[i] == str[i] && str[i] != '=' && env[i] != '\0')
		i++;
	if (env[i] == '=' || (env[i] == '\0' && str[i] == '='))
		return (0);
	return (-1);
}

static char	**new_env_aux(char **aux, char *str, int i)
{
	int	p;

	p = 0;
	while (str[p] != '\0')
	{
		aux[i][p] = str[p];
		p++;
	}
	aux[i][p] = '\0';
	aux [i + 1] = NULL;
	return (aux);
}

static char	**new_env(char **env, int size, char *str)
{
	int		i;
	int		p;
	char	**aux;

	i = 0;
	aux = (char **)malloc((size) * sizeof(char *));
	while (env[i])
	{
		p = 0;
		aux[i] = (char *)malloc((ft_strlen(env[i]) + 1) * sizeof(char));
		while (env[i][p] != '\0')
		{
			aux[i][p] = env[i][p];
			p++;
		}
		aux[i][p] = '\0';
		i++;
	}
	aux[i] = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	return (new_env_aux(aux, str, i));
}

void	ft_export(t_envir *env, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	if (!str)
		return ;
	while (env->e_envp[i] && find_env(env->e_envp[i], str))
		i++;
	if (env->e_envp[i] != NULL)
		ft_unset(env, str);
	aux = new_env(env->e_envp, ft_env(env->e_envp, 1) + 2, str);
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
