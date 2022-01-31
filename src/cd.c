/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:40:04 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/31 15:05:23 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path, t_envir *env)
{
	char	*dir;
	char	*aux;

	dir = NULL;
	dir = getcwd(dir, 0);
	aux = ft_strjoin("OLDPWD=", dir);
	ft_export(env, aux);
	chdir(path);
	free(dir);
	free(aux);
	dir = NULL;
	aux = NULL;
	dir = getcwd(dir, 0);
	aux = ft_strjoin("PWD=", dir);
	ft_export(env, aux);
	free(dir);
	free(aux);
	return (0);
}
