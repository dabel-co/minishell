/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/11 18:10:52 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int find_env_expand(char *env, char *tofind)
{
	
}
static int	check_env_expand(char *str, t_envir env)
{

}

static char* get_env_expand(char *str,  t_envir env)
{

}

char *expand_line(char *str, t_envir *env)
{
	int i;
	char *result;
	char *aux;
	int p;

	result = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$' && check_expand(&str[i], env))
		{
			aux = ft_strdup(&str[i]);
			result = ft_strjoin_free(result, get_env_expand(&str[i]str, env));
			i = i + check_expand(&str[i], env);
			p = ft_strlen(result);
			result = ft_strjoin_free(result, aux);
			free (aux);
		}
		else
			result[p] = str[i];
		p++;
		i++;
	}
	result[p] = '\0';
	return (result);
}
