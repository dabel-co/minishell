/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:14:37 by marvin            #+#    #+#             */
/*   Updated: 2022/01/18 14:45:44 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **to_print)
{
	while(*to_print)
		ft_putendl_fd(*to_print++, 1);
}

void	exec_pipe(char *comm, int rfd, int *pip)
{
	t_execord	exec_order;

	exec_order.ignore = 0;
	rfd = input_redir(&comm, rfd/*, &exec_order*/);
	pip[WR_END] = output_redir(&comm, pip[WR_END]);
	
}

void	exec_manage(char **orders)
{
	int	ind;
	int	pip[2][2];

	ind = 0;
	while (orders[ind + 1])
	{
		if (pipe(pip[ind % 2]) < 0)
		{
			close(pip[ind % 2][RD_END]);
			close(pip[ind % 2][WR_END]);
			return ;
		}
		exec_pipe(orders[ind], pip[ind % 2 + 1][RD_END], pip[ind % 2]);
		ind++;
	}
	exec_fd(orders[ind], pip[ind % 2][RD_END]);
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
		orders = ft_split(comm_line, '|');
		//exec_manage(orders);
		print_array(orders);
	}
}
