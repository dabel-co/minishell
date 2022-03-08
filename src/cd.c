/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:40:04 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/08 16:47:42 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path, t_envir *env) //HAY QUE ESTA FUNCIÓN NO ACTUALICE OLDPWD Y PWD A NO SER QUE TODO SALGA BIEN, Y QUE IMPRIMA MENSAJE DE ERROR EN CASO DE QUE NO SALGA BIEN
{
	char	*dir;
	char	*aux;

	dir = NULL;
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
