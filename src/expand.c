/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:46:32 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/19 17:37:20 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//probably should mode this somewhere later when we have it figured out

char	*expand(char *str, t_envir *env)
{
	int		i;
	int		p;
	char	*aux;

	i = 0;
	p = 0;
	str++;
	while (find_env(env->e_envp[i], str))
		i++;
	while (env->e_envp[i][p] != '=')
		p++;
	aux = malloc(ft_strlen(&env->e_envp[i][p]) * sizeof(char));
	ft_strlcpy(aux, &env->e_envp[i][p + 1], ft_strlen(&env->e_envp[i][p]) + 1);
	return (aux);
}
