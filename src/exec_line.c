/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:14:37 by marvin            #+#    #+#             */
/*   Updated: 2022/01/03 17:14:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **to_print)
{
	while(*to_print)
		ft_putendl_fd(*to_print++, 1);
}

void	exec_line(char *comm_line, t_envir *env)
{
	//t_execord	exec_order;
	char		**orders;

	(void)env;
	if (!comm_line || !comm_line[0])
		ft_putstr_fd("", 1);
	else
	{
		orders = ord_split(comm_line);
		print_array(orders);
	}
}