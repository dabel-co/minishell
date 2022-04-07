/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:40:04 by dabel-co          #+#    #+#             */
/*   Updated: 2022/04/07 11:52:59 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(char *dir, t_envir *env)
{
	char	*aux;

	if (dir)
	{
		aux = ft_strjoin("OLDPWD=", dir);
		home_export(aux, env, 0);
		free(dir);
		free(aux);
	}
	dir = getcwd(NULL, 0);
	if (dir)
	{
		aux = ft_strjoin("PWD=", dir);
		home_export(aux, env, 0);
		free(dir);
		free(aux);
	}
	return (0);
}

int	ft_cd(char *path, t_envir *env)
{
	char	*dir;
	char	*err_prompt;
	char	**home;

	if (!path)
	{
		home = env_search(env->e_envp, "HOME", 4);
		if (home)
			path = *home + 5;
	}
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	if (!*path)
		path = ".";
	dir = getcwd(NULL, 0);
	if (!chdir(path))
		return (update_env(dir, env));
	err_prompt = ft_strjoin("minishell: cd: ", path);
	perror(err_prompt);
	free(err_prompt);
	free(dir);
	return (1);
}
