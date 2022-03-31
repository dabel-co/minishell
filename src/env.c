/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:38:57 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 18:43:00 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env_print, int wfd)
{
	while (*env_print)
	{
		if (ft_strchr(*env_print, '='))
			ft_putendl_fd(*env_print, wfd);
		env_print++;
	}
	return (0);
}
