/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/15 14:08:58 by vguttenb         ###   ########.fr       */
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
	//add stop at =
	t = 0;
	result = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$' && t == 0)
		{
			result = ft_strjoin_free(result, get_env_value(&str[i], env));
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
	free(str);
	return (result);
}

// char	*expand_line(char *line, t_envir *env)
// {
// 	char	*ret;
// 	char	*var;
// 	int		start;
// 	int		ind;

// 	ret = NULL;
// 	ind = 0;
// 	while (line[ind])
// 	{
// 		start = ind;
// 		while (line[ind])
// 		{
// 			if (line[ind] == '\'')
// 				while (line[++ind] != '\''); //DE ESTO SE VA A QUEJAR LA NORMA
// 			if (line[ind] == '$' && line[ind + 1] && !ft_strchr(" =", line[ind + 1]))
// 				break ;
// 			ind++;
// 		}
// 		ret = ft_strjoin_free(ret, ft_substr(line, start, (ind - start)));
// 		if (line[ind])
// 			ind++;
// 		start = ind;
// 		while (line[ind] && !ft_strchr(" =\"\'", line[ind]))
// 			ind++;
// 		var = env_retrieve(ft_substr(line, start, (ind - start)), env, 1);
// 		if (var)
// 			ret = ft_strjoin_free(ret, var);
// 		free(var);
// 	}
// 	free(line);
// 	return (ret);
// }
