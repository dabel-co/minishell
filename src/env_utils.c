/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/04 12:13:50 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		ft_putendl_fd(str[i], STDOUT_FILENO);
		i++;
	}
}
static	int	find_env(char *env, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != env[i])
			return (-1);
		i++;
	}
	if (env[i] == '=')
			return (0);
	return (-1);
}

void	ft_unset(t_envir *env, char *str)
{
	int	i;

	i = 0;
	ft_env(env->e_envp);
	while (find_env(env->e_envp[i], str))
		i++;
	if (env->e_envp[i] == NULL)
		return ;
	free(env->e_envp[i]);
	while (env->e_envp[i + 1])
	{
		env->e_envp[i] = env->e_envp[i + 1];
		i++;
	}
	free(env->e_envp[i + 1]);
	env->e_envp[i] = NULL;
	ft_env(env->e_envp);
}
