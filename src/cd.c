/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:40:04 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/09 13:06:03 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_home(char *path, t_envir *env, char *dir, char *aux)
{
	char	*new_path;

	if (path)
		return (-1);
	new_path = get_env_value("$HOME", env);
	if (!new_path)
	{
		printf("HEAOIJJJGOI ADD HOME NOT SET PROPERLY\n");
		return (-1);
	}
	dir = getcwd(dir, 0);
	aux = ft_strjoin("OLDPWD=", dir);
	ft_export(env, aux, 0);
	chdir(new_path);
	free(new_path);
	free(dir);
	free(aux);
	dir = NULL;
	aux = NULL;
	dir = getcwd(dir, 0);
	aux = ft_strjoin("PWD=", dir);
	ft_export(env, aux, 0);
	free(dir);
	free(aux);
	return (0);
}

int	check_valid_path(char *path, char *dir)
{
	dir = getcwd(dir, 0);
	if (chdir(path) == -1)
	{
		printf("INVALID PATH I'M NOT GOING TOO WORK LOL IMPLEMENT ERRNO\n");
		return (0);
	}
	chdir(dir);
	return (-1);
}

int	ft_cd(char *path, t_envir *env)
{
	char	*dir;
	char	*aux;

	dir = NULL;
	if (!check_home(path, env, dir, NULL))
		return (0);
	if (!check_valid_path(path, dir))
		return (0);
	dir = getcwd(dir, 0);
	aux = ft_strjoin("OLDPWD=", dir);
	ft_export(env, aux, 0);
	chdir(path);
	free(dir);
	free(aux);
	dir = NULL;
	aux = NULL;
	dir = getcwd(dir, 0);
	aux = ft_strjoin("PWD=", dir);
	ft_export(env, aux, 0);
	free(dir);
	free(aux);
	return (0);
}
