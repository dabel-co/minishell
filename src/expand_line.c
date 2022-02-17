/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/15 18:30:29 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	check_env_expand(char *str)
{
	int i;

	i = 1;
	//printf("EMPEZAMOS EN %c\n", str[i]);
	while (str[i] != ' ' && str[i] != '\0')
	{
		i++;
	//	printf("%s\n", &str[i]);
	}
	if (str[i] == '\0')
		return (i - 1);
	return (i);
}

static int	find_env_expand(char *env, char *str)
{
	int i;

	i = 0;
	while (env[i] == str[i + 1])
		i++;
	if (env[i] == '=' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		return (0);
	return (-1);
}

static char* get_env_expand(char *str,  t_envir *env)
{
	int i;
	char *aux;
	int p;
	int x;

	i = 0;
	p = 0;
	x = 0;
	while (env->e_envp[i] && find_env_expand(env->e_envp[i], str))
		i++;
	//printf("VAMOS A COPIAR ->%s\n", env->e_envp[i]);
	if (env->e_envp[i] == NULL)
		return (NULL);
	while (env->e_envp[i][x] != '=')
		x++;
	x++;
	aux = malloc((ft_strlen(&env->e_envp[i][x]) + 1) * sizeof(char));
	while (env->e_envp[i][x])
	{
		aux[p] = env->e_envp[i][x];
		p++;
		x++;
	}
	aux[p] = '\0';
	//printf("---------%s\n", aux);
	return (aux);
}

char *expand_line(char *str, t_envir *env)
{
	int i;
	char *result;
	char *aux;
	int p;
	int t;

	i = 0;
	p = 0;
	t = 0;
	result = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$' && t == 0)
		{
			aux = ft_strdup(&str[i]);
			//printf("esto deberia ser el resto de la cadena %s\n", aux);
			//printf("a ver result %s\n", result);
			//printf("a ver expand line %s\n", get_env_expand(&str[i], env));
			result = ft_strjoin_free(result, get_env_expand(&str[i], env));
			printf("esto deberia ser la cadena de antes con expansion %s\n", result);
			i = i + check_env_expand(&str[i]);
			printf("esto deberia ser el resto que quede por copiar %s\n", &str[i]);
			p = ft_strlen(result);
			result = ft_strjoin_free(result, &str[i]);
			free (aux);
		}
		else
		{
			result[p] = str[i];
			result[p + 1] = '\0';
		}
		if (str[i] == '\'' && t == 0)
			t = 1;
		else if (str[i] == '\'' && t == 1)
			t = 0;
		p++;
		if (str[i] != '\0')
			i++;
	}
	result[p] = '\0';
	return (result);
}
