/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/14 11:21:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_paths(t_envir *env)
{
	int	i;

	i = 0;
	while (env->paths[i])
	{
		free(env->paths[i]);
		i++;
	}
	free(env->paths);
	env->paths = get_paths(env->e_envp);
}

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

static char	**new_env_aux(char **aux, char *str, int i)
{
	int	p;

	p = 0;
	while (str[p] != '\0')
	{
		aux[i][p] = str[p];
		p++;
	}
	aux[i][p] = '\0';
	aux [i + 1] = NULL;
	return (aux);
}

static char	**new_env(char **env, int size, char *str)
{
	int		i;
	int		p;
	char	**aux;

	i = 0;
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
	return (new_env_aux(aux, str, i));
}

int	ft_export(t_envir *env, char *str, int wfd)
{
	int		i;
	char	**aux;

	i = 0;
	if (!str)
		ft_env(env->e_envp, 2, wfd);
	if (!str || str[1] == '$')
		return ;
	if (str[0] == '$') //fix this thingy
		str++;
	while (env->e_envp[i] && find_env(env->e_envp[i], str))
		i++;
	if (env->e_envp[i] != NULL)
		ft_unset(env, str);
	aux = new_env(env->e_envp, ft_env(env->e_envp, 1, 0) + 2, str);
	i = 0;
	while (env->e_envp[i])
	{
		free(env->e_envp[i]);
		i++;
	}
	free(env->e_envp);
	env->e_envp = aux;
	if (ft_strncmp("PATH=", str, 5))
		update_paths(env);
	return (0);
}

/*int	is_valid_id(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (0);
	while (*str && *str != '=')
	{
		if (*str == '$' || *str == ' ')
			return (0);
		str++;
	}
	return (1);
}

char	**env_search(char **env, char *to_search, int name_size)
{
	while (*env)
	{
		if (ft_strnstr(*env, to_search, name_size)
			&& (!*env[name_size] || *env[name_size] == '='))
			return(env);
		env++;
	}
	return (NULL);
}

int	env_replace(char *str, t_envir *env)
{
	int		name_size;
	char	**to_replace;

	name_size = 0;
	while (str[name_size] && str[name_size] != '=')
		name_size++;
	to_replace = env_search(env->envp, str, name_size);
	if (!to_replace)
		return (0);
	if (str[name_size] || !*to_replace[name_size])
	{
		free(*to_replace);
		*to_replace = ft_strdup(str);
		if (ft_strnstr("PATH=", str, 5))
			update_paths(env);
	}
	str[0] = '\0';
	return (1);
}

void	env_update(t_envir *env, char **argv, int new_var)
{
	char	**new_env;
	int		old_var;
	int		iter;

	while (env->e_envp[old_var])
		old_var++;
	new_env = (char**)malloc(sizeof(char*) * (old_var + new_var + 1));
	iter = 0;
	while (iter < old_var)
	{
		new_env[iter] = env->e_envp[iter];
		iter++;
	}
	if (new_var)
	{
		while (*argv)
		{
			if (*argv[0])
				new_env[iter++] = ft_strdup(*argv);
			argv++;
		}
	}
	new_env[iter] = NULL;
	free(env->e_envp);
	env->e_envp = new_env;
}

void	env_remove(char *to_remove, t_envir *env, int name_size)
{
	char	**old_var;

	old_var = env_search(env->envp, to_remove, name_size);
	if (!old_var)
		return ;
	free(*old_var);
	while (*(old_var + sizeof(char *)))
		*old_var = *(old_var + sizeof(char *));
}

int	ft_unset(t_envir *env, char **argv)
{
	int		ret;
	int		name_size;

	ret = 0;
	while (*argv)
	{
		if (!is_valid_id(*argv))
		{
			ret = 1;
			ft_putstr_fd("minishell: unset: not a valid identifier: `", STDERR_FILENO);
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			argv++;
			break ;
		}
		name_size = 0;
		while (*argv[name_size] && *argv[name_size] != '=')
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
	if (!*argv)
		ft_env(env->e_envp, 2, wfd);
	iter = argv;
	while (*iter)
	{
		if (!is_valid_id(iter))
		{
			ret = 1;
			ft_putstr_fd("minishell: export: not a valid identifier: `", STDERR_FILENO);
			ft_putstr_fd(*iter, STDERR_FILENO);
			ft_putendl_fd("'", STDERR_FILENO);
			*iter[0] = '\0';
		}
		else if (!env_replace(iter, env))
			new_var++;
		iter++;
	}
	update_env(env, argv, new_var);
	return (ret);
}
