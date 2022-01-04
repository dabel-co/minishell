/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/04 18:36:11 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env(char *env, char *str)
{
	int	i;

	i = 0;
	i = 0;
	printf("TEST\n");
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

static char	**new_env(char **env, int size, char *str)
{
	int i;
	int p;
	char **aux;
//add path thingy
	i = 0;
	printf("TEST\n");
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
	p = 0;
	while (str[p] != '\0')
	{
		aux[i][p] = str[p];
		p++;
	}
	aux[i + 1] = NULL; 
	return (aux);
}

void	ft_export(t_envir *env, char *str)
{
	ft_env(env->e_envp, 0);
	printf("\n");
	int i;
	char **aux;

	i = 0;
	printf("TEST\n");
	while (env->e_envp[i] && find_env(env->e_envp[i], str))
		i++;
	printf("TESTAAA\n");
	if (env->e_envp[i] != NULL)
		ft_unset(env, str);
	printf("TEST\n");
	aux = new_env(env->e_envp, ft_env(env->e_envp, 1) + 2, str);
	i = 0;
	while (env->e_envp[i])
	{
		free(env->e_envp[i]);
		i++;
	}
	free(env->e_envp);
	env->e_envp = aux;
	ft_env(env->e_envp, 0);
	printf("\n");
}
