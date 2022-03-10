/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:37:38 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/10 14:10:41 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *str, t_envir *env)
{
	int		i;
	char	*aux;
	int		p;
	int		x;

	i = 0;
	p = 0;
	x = 0;
	while (env->e_envp[i] && find_env_expand(env->e_envp[i], str))
		i++;
	if (env->e_envp[i] == NULL)
		return (NULL);
	while (env->e_envp[i][x] != '=')
		x++;
	x++;
	aux = malloc((ft_strlen(&env->e_envp[i][x]) + 1) * sizeof(char));
	while (env->e_envp[i][x])
	{
		aux[p] = env->e_envp[i][x];
		p++;
		x++;
	}
	aux[p] = '\0';
	return (aux);
}
/* Mode = 0 will make this function behave like a regular env,
 * Mode = 2 will make it display the output of a export with no parameters */

int	ft_env(char **str, int mode, int wfd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (mode == 2 && str[i][0] != '?')
			ft_putstr_fd("declare -x ", wfd);
		if (((mode == 0 && ft_strchr(str[i], '=')) || mode == 2) && str[i][0] != '?')
			ft_putendl_fd(str[i], wfd);
		i++;
	}
	return (i);
}
