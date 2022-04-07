/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:27:36 by dabel-co          #+#    #+#             */
/*   Updated: 2022/04/07 13:03:41 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_envir *env, char **argv)
{
	int		new_var;
	int		ret;
	char	**iter;

	ret = 0;
	new_var = 0;
	if (!*++argv)
		return (ret);
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
