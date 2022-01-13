/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/13 15:50:20 by dabel-co         ###   ########.fr       */
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
	int		p;
	int		s;
	char	**aux;

	i = 0;
	s = 0;
	aux = (char **)malloc((size) * sizeof(char *));
	while (env[s])
	{
		p = 0;
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

int	ft_env(char **str, int mode)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (mode == 2)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if ((mode == 0 && ft_strchr(str[i], '=')) || mode == 2)
			ft_putendl_fd(str[i], STDOUT_FILENO);
		i++;
	}
	return (i);
}

void	ft_unset(t_envir *env, char *str)
{
	int		i;
	char	**aux;

	i = 0;
	while (find_env(env->e_envp[i], str))
		i++;
	if (env->e_envp[i] == NULL)
		return ;
	aux = new_env(env->e_envp, ft_env(env->e_envp, 1), str);
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
