/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/31 13:00:23 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_env_expand(char *str)
// {
// 	int	i;

// 	i = 1;
// 	while (str[i] != ' ' && str[i] != '\0' && str[i] != '$' && str[i] != '"')
// 		i++;
// 	if (str[i] == '\0')
// 		return (i - 1);
// 	return (i);
// }

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

// static int	advance_and_check_quote(int *t, char c, char str)
// {
// 	if (c == '\'' && *t == 1)
// 		*t = 0;
// 	else if (c == '\'' && *t == 0)
// 		*t = 1;
// 	if ((str != '\0' && str != '$') || (*t == 1 && str == '$'))
// 		return (1);
// 	return (0);
// }

// char	*expand_line_aux(char *result, char str, int p)
// {
// 	result[p] = str;
// 	result[p + 1] = '\0';
// 	return (result);
// }

// char	*expand_line(char *str, t_envir *env, int i, int p)
// {
// 	char	*result;
// 	int		t;
// 	//add stop at =
// 	t = 0;
// 	result = malloc(ft_strlen(str) + 1);
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && t == 0)
// 		{
// 			result = ft_strjoin_free(result, get_env_value(&str[i], env));
// 			i = i + check_env_expand(&str[i]);
// 			p = ft_strlen(result);
// 			if ((str[i + 1] != '\0' && str[i + 1] != '$' && str[i] != '$')
// 				|| str[i] == '"')
// 				result = ft_strjoin_free(result, &str[i]);
// 		}
// 		else
// 			result = expand_line_aux(result, str[i], p);
// 		i = i + advance_and_check_quote(&t, str[i], str[i]);
// 		if (result[p] != '\0')
// 			p++;
// 	}
// 	result[p] = '\0';
// 	free(str);
// 	return (result);
// }

// char	*env_retrieve(char *line, t_envir *env, int	*ind)
// {
// 	int		start;
// 	int		name_size;
// 	char	*var_name;
// 	char	**var_value;

// 	start = *ind;
// 	if (line[*ind] == '?')
// 	{
// 		*ind += 1;	
// 		return (ft_itoa(env->zyzz));
// 	}
// 	if (!line[*ind] || !ft_isalnum(line[*ind]));
// 		return (ft_strdup("$"));
// 	while (line[*ind] && ft_isalnum(line[*ind]))
// 		*ind += 1;
// 	name_size = *ind - start;
// 	var_name = ft_substr(line, start, name_size);
// 	var_value = env_search(env, var_name, name_size);
// 	free(var_name);
// 	if (!var_value || !var_value[0][name_size] || !var_value[0][name_size + 1])
// 		return (NULL);
// 	var_name = *var_value + name_size + 1;
// 	return (ft_strdup(var_name));
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
	if (!line[*ind] || (!ft_isalnum(line[*ind]) && line[*ind] != '_'))
		return (ft_strdup("$"));
	name_size = 0;
	while (line[*ind + name_size] && (ft_isalnum(line[*ind + name_size]) || line[*ind + name_size] == '_'))
		name_size++;
	*ind += name_size;
	return (env_retrieve(ft_substr(line, (*ind - name_size), name_size), env, 1));
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
// 		while (line[ind] && line[ind] != '$')
// 		{
// 			if (line[ind] == '\"')
// 				while (line[++ind] != '\"'); //DE ESTO SE VA A QUEJAR LA NORMA
// 			// if (line[ind] == '$' && line[ind + 1] && ft_isalnum(line[ind + 1]))
// 			// 	break ;
// 			ind++;
// 		}
// 		ret = ft_strjoin_free(ret, ft_substr(line, start, (ind - start)));
// 		// if (line[ind])
// 		// 	ind++;
// 		// start = ind;
// 		// while (line[ind] && !ft_strchr(" =$\"\'", line[ind]))
// 		// 	ind++;
// 		var = env_retrieve(line, env, &ind);
// 		if (var)
// 			ret = ft_strjoin_free(ret, var);
// 		free(var);
// 	}
// 	free(line);
// 	return (ret);
// }

int		find_next_var(char *line, int ind, char *limiter)
{
	while (line[ind])
	{
		if ((line[ind] == '\'' || line[ind] == '\"') && !*limiter)
			*limiter = line[ind];
		else if ((line[ind] == '\'' || line[ind] == '\"') && line[ind] == *limiter)
			*limiter = '\0';
		else if (line[ind] == '$' && *limiter != '\'')
			break ;
		ind++;
	}
	
	// while (line[ind] && line[ind] != '$')
	// 	if (line[ind++] == '\'')
	// 		while(line[ind])
	// 			if (line[ind++] == '\'')
	// 				break ;
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

// char	*expand_line(char *line, t_envir *env)
// {
// 	char	*ret;
// 	char	*new;
// 	int		start;
// 	int		ind;

// 	ret = NULL;
// 	ind = 0;
// 	line = ft_strtrim_free(line, " ");
// 	if (!*line)
// 		return (line);
// 	while (line[ind])
// 	{
// 		start = ind;
// 		ind = find_next_var(line, ind);
// 		// while (line[ind] && line[ind] != '$')
// 		// 	if (line[ind++] == '\'')
// 		// 		while (line[ind++] != '\'');
// 		new = ft_substr(line, start, (ind - start));
// 		ret = ft_strjoin_free(ret, new);
// 		free(new);
// 		new = get_var_value(line, env, &ind);
// 		if (new)
// 			ret = ft_strjoin_free(ret, new);
// 			// ret = ft_strjoin_free(ft_strjoin_free(\
// 			// ft_strjoin_free(ret, "'"), new), "'");
// 		free(new);
// 	}
// 	free(line);
// 	return (ret);
// }