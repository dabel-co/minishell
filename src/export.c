/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/30 19:33:43 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env(char *env, char *str)
{
	int	i;

	i = 0;
	if (!env || !str || env == NULL)
		return (-1);
	while (env[i] == str[i] && str[i] != '=' && env[i] != '\0')
		i++;
	if (env[i] == '=' || (env[i] == '\0' && str[i] == '='))
		return (0);
	return (-1);
}

// static char	**new_env_aux(char **aux, char *str, int i)
// {
// 	int	p;

// 	p = 0;
// 	while (str[p] != '\0')
// 	{
// 		aux[i][p] = str[p];
// 		p++;
// 	}
// 	aux[i][p] = '\0';
// 	aux [i + 1] = NULL;
// 	return (aux);
// }

// static char	**new_env(char **env, int size, char *str)
// {
// 	int		i;
// 	int		p;
// 	char	**aux;

// 	i = 0;
// 	aux = (char **)malloc((size) * sizeof(char *));
// 	while (env[i])
// 	{
// 		p = 0;
// 		aux[i] = (char *)malloc((ft_strlen(env[i]) + 1) * sizeof(char));
// 		while (env[i][p] != '\0')
// 		{
// 			aux[i][p] = env[i][p];
// 			p++;
// 		}
// 		aux[i][p] = '\0';
// 		i++;
// 	}
// 	aux[i] = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
// 	return (new_env_aux(aux, str, i));
// }

// int	ft_export(t_envir *env, char *str, int wfd)
// {
// 	int		i;
// 	char	**aux;

// 	i = 0;
// 	if (!str)
// 		ft_env(env->e_envp, 2, wfd);
// 	if (!str || str[1] == '$')
// 		return (0);
// 	if (str[0] == '$') //fix this thingy
// 		str++;
// 	while (env->e_envp[i] && find_env(env->e_envp[i], str))
// 		i++;
// 	if (env->e_envp[i] != NULL)
// 		ft_unset(env, str);
// 	aux = new_env(env->e_envp, ft_env(env->e_envp, 1, 0) + 2, str);
// 	i = 0;
// 	while (env->e_envp[i])
// 	{
// 		free(env->e_envp[i]);
// 		i++;
// 	}
// 	free(env->e_envp);
// 	env->e_envp = aux;
// 	if (ft_strncmp("PATH=", str, 5))
// 		update_paths(env);
// 	return (0);
// }

int	is_valid_id(char *str, int unset_mode)
{
	if (!*str || ft_isdigit(*str))
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (*str && unset_mode)
		return (0);
	return (1);
}

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
	return(env);
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
	new_env = (char**)malloc(sizeof(char*) * (old_var + new_var + 1));
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

void	env_home_export(char *new_var, t_envir *env, int free_flag)
{
	char	*to_export[3];

	to_export[0] = NULL;
	to_export[1] = ft_strdup(new_var);
	to_export[2] = NULL;
	ft_export(env, to_export, 0);
	free(to_export[1]);
	if (free_flag)
		free(new_var);
}

int	ft_env(char **env_print, int wfd)
{
	while (*env_print)
	{
		if (ft_strchr(*env_print, '='))
			ft_putendl_fd(*env_print, wfd);
		env_print++;
	}
	return (0);
}

int	ft_unset(t_envir *env, char **argv)
{
	int		ret;
	int		name_size;

	ret = 0;
	argv++;
	while (*argv)
	{
		if (!is_valid_id(*argv, 1))
		{
			ret = 1;
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			argv++;
			break ;
		}
		name_size = 0;
		while (argv[0][name_size] && argv[0][name_size] != '=')
			name_size++;
		env_remove(*argv, env, name_size);
		argv++;
	}
	env_update(env, NULL, 0);
	return (ret);
}

int	ft_export(t_envir *env, char **argv, int wfd)
{
	int		new_var;
	int		ret;
	char	**iter;

	ret = 0;
	new_var = 0;
	if (!*++argv)
		ft_env(env->e_envp, /*2, */wfd);
	iter = argv;
	while (*iter)
	{
		if (!is_valid_id(*iter, 0))
		{
			ret = 1;
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(*iter, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			iter[0][0] = '\0';
		}
		else if (!env_replace(*iter, env))
			new_var++;
		iter++;
	}
	env_update(env, argv, new_var);
	return (ret);
}
