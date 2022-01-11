/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/11 15:56:36 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		aux[i] = (char *)malloc((ft_strlen(env[s]) + 1) * sizeof(char));
		while (env[s][p] != '\0')
		{
			aux[i][p] = env[s][p];
			p++;
		}
		aux[i][p] = '\0';
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
		if (mode == 0)
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
}
