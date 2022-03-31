/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:30:09 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 17:06:17 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
