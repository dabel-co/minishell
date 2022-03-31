/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:28:01 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 18:43:35 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_search(char **env, char *to_search, int name_size)
{
	char	*name;

	name = ft_substr(to_search, 0, name_size);
	while (*env)
	{
		if (ft_strnstr(*env, name, name_size)
			&& (!env[0][name_size] || env[0][name_size] == '='))
			break ;
		env++;
	}
	free(name);
	if (!*env)
		return (NULL);
	return (env);
}

char	*env_retrieve(char *var, t_envir *env, int free_flag)
{
	int		name_size;
	char	**var_value;

	name_size = ft_strlen(var);
	var_value = env_search(env->e_envp, var, name_size);
	if (free_flag)
		free(var);
	if (!var_value || !var_value[0][name_size] || !var_value[0][name_size + 1])
		return (NULL);
	return (ft_strdup(&var_value[0][name_size + 1]));
}

int	env_replace(char *str, t_envir *env)
{
	int		name_size;
	char	**to_replace;

	name_size = 0;
	while (str[name_size] && str[name_size] != '=')
		name_size++;
	to_replace = env_search(env->e_envp, str, name_size);
	if (!to_replace)
		return (0);
	if (str[name_size] || !to_replace[0][name_size])
	{
		free(*to_replace);
		*to_replace = ft_strdup(str);
		if (ft_strnstr(str, "PATH=", 5))
			env->paths = update_paths(env);
	}
	str[0] = '\0';
	return (1);
}

void	env_update(t_envir *env, char **argv, int new_var)
{
	char	**new_env;
	int		old_var;
	int		iter;

	old_var = 0;
	while (env->e_envp[old_var])
		old_var++;
	new_env = (char **)malloc(sizeof(char *) * (old_var + new_var + 1));
	iter = -1;
	while (++iter < old_var)
		new_env[iter] = env->e_envp[iter];
	old_var = 0;
	while (argv && *argv)
	{
		if (*argv[0])
			new_env[iter++] = ft_strdup(*argv);
		if (ft_strnstr(*argv, "PATH=", 5))
			old_var++;
		argv++;
	}
	new_env[iter] = NULL;
	free(env->e_envp);
	env->e_envp = new_env;
	if (old_var)
		env->paths = update_paths(env);
}

void	env_remove(char *to_remove, t_envir *env, int name_size)
{
	char	**old_var;

	old_var = env_search(env->e_envp, to_remove, name_size);
	if (!old_var)
		return ;
	free(*old_var);
	while (*(old_var + 1))
	{
		*old_var = *(old_var + 1);
		old_var++;
	}
	*old_var = NULL;
	if (ft_strnstr(to_remove, "PATH", 4))
		env->paths = update_paths(env);
}
