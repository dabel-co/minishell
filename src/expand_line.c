/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/22 18:04:53 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_env_expand(char *str)
{
	int	i;

	i = 1;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '$' && str[i] != '"')
		i++;
	if (str[i] == '\0')
		return (i - 1);
	return (i);
}

int	find_env_expand(char *env, char *str)
{
	int	i;

	i = 0;
	while (env[i] == str[i + 1])
		i++;
	if (env[i] == '=' && (str[i + 1] == ' ' || str[i + 1] == '\0'
			|| str[i + 1] == '$' || str[i + 1] == '"'))
		return (0);
	return (-1);
}

static int	advance_and_check_quote(int *t, char c, char str)
{
	if (c == '\'' && *t == 1)
		*t = 0;
	else if (c == '\'' && *t == 0)
		*t = 1;
	if ((str != '\0' && str != '$') || (*t == 1 && str == '$'))
		return (1);
	return (0);
}

char	*expand_line_aux(char *result, char str, int p)
{
	result[p] = str;
	result[p + 1] = '\0';
	return (result);
}

char	*expand_line(char *str, t_envir *env, int i, int p)
{
	char	*result;
	int		t;

	t = 0;
	result = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$' && t == 0)
		{
			result = ft_strjoin_free(result, env_expand_aux(&str[i], env));
			i = i + check_env_expand(&str[i]);
			p = ft_strlen(result);
			if ((str[i + 1] != '\0' && str[i + 1] != '$' && str[i] != '$')
				|| str[i] == '"')
				result = ft_strjoin_free(result, &str[i]);
		}
		else
			result = expand_line_aux(result, str[i], p);
		i = i + advance_and_check_quote(&t, str[i], str[i]);
		if (result[p] != '\0')
			p++;
	}
	result[p] = '\0';
	return (result);
}
