/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:59:04 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/13 16:13:05 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(t_exec *node, t_envir *env)
{
	if (!ft_strcmp(node->argv[0], "exit"))
		return (0);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!node->argv[1])
		return (1);
	if (!is_all_num(node->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(node->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		env->zyzz = 255;
		return (1);
	}
	if (!node->argv[2])
	{
		env->zyzz = ft_atoi(node->argv[1]);
		return (1);
	}
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (0);
}
