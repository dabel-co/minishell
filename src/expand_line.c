/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/31 18:41:03 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	find_env_expand(char *env, char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] == str[i + 1])
// 		i++;
// 	if (env[i] == '=' && (str[i + 1] == ' ' || str[i + 1] == '\0'
// 			|| str[i + 1] == '$' || str[i + 1] == '"'))
// 		return (0);
// 	return (-1);
// }

static char	*get_var_value(char *line, t_envir *env, int *ind, char limiter)
{
	int		name_size;

	if (!line[*ind])
		return (NULL);
	*ind += 1;
	if (line[*ind] == '?')
	{
		*ind += 1;
		return (ft_itoa(env->zyzz));
	}
	if ((line[*ind] == '\'' || line[*ind] == '\"') && !limiter)
		return (NULL);
	if (!line[*ind] || \
	(!ft_isalnum(line[*ind]) && line[*ind] != '_'))
		return (ft_strdup("$"));
	name_size = 0;
	while (line[*ind + name_size] && \
	(ft_isalnum(line[*ind + name_size]) || line[*ind + name_size] == '_'))
		name_size++;
	*ind += name_size;
	return (env_retrieve(ft_substr(line, \
	(*ind - name_size), name_size), env, 1));
}

static int	find_next_var(char *line, int ind, char *limiter)
{
	while (line[ind])
	{
		if ((line[ind] == '\'' || line[ind] == '\"') && !*limiter)
			*limiter = line[ind];
		else if ((line[ind] == '\'' || line[ind] == '\"') \
		&& line[ind] == *limiter)
			*limiter = '\0';
		else if (line[ind] == '$' && *limiter != '\'')
			break ;
		ind++;
	}
	return (ind);
}

char	*expand_line(char *line, t_envir *env, char limiter)
{
	char	*ret;
	char	*new;
	int		start;
	int		ind;

	ret = NULL;
	ind = 0;
	line = ft_strtrim_free(line, " ");
	if (!*line)
		return (line);
	while (line[ind])
	{
		start = ind;
		ind = find_next_var(line, ind, &limiter);
		new = ft_substr(line, start, (ind - start));
		ret = ft_strjoin_free(ret, new);
		free(new);
		new = get_var_value(line, env, &ind, limiter);
		if (new)
			ret = ft_strjoin_free(ret, new);
		free(new);
	}
	free(line);
	return (ret);
}
