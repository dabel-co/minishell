/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:37:38 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/03 11:18:46 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **str, int mode)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (mode == 2)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if ((mode == 0 && ft_strchr(str[i], '=')) || mode == 2)
			ft_putendl_fd(str[i], STDOUT_FILENO);
		i++;
	}
	return (i);
}
