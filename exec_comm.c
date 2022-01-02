/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:14:39 by marvin            #+#    #+#             */
/*   Updated: 2022/01/02 17:14:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_execord *execorder, char **envp)
{
	pid_t		pidC;

	pidC = fork();
	if (pidC == -1)
		perror("fork");
	else if (pidC == 0)
	{
		if (execve(execorder->comm, execorder->argsum, envp) < 0)
		{
			perror(execorder->argsum[0]);
			exit (0);
		}
	}
	else
		waitpid(pidC, NULL, 0);
}

static void	execfree(t_execord *exec_order)
{
	int	ind;

	if (exec_order->free && exec_order->comm)
		free(exec_order->comm);
	ind = 0;
	while (exec_order->argsum[ind])
	{
		free(exec_order->argsum[ind]);
		ind++;
	}
	free(exec_order->argsum);
}

static void	get_execord(char *command, char **paths, t_execord *exec_order)
{
	char		**complus;
	char		*last_bar;


	//printf("%s\n", command);
	complus = ft_split(command, ' ');
	last_bar = ft_strrchr(complus[0], '/');
	if (last_bar)
	{
		exec_order->comm = command;
		if (access(exec_order->comm, F_OK) < 0)
			exec_order->comm = NULL;
		exec_order->argsum = complus;
		last_bar = ft_strdup(last_bar + sizeof(char));
		free(complus[0]);
		exec_order->argsum[0] = last_bar;
		exec_order->free = 0;
	}
	else
	{
		exec_order->comm = search_comm(complus[0], paths);
		exec_order->argsum = complus;
		exec_order->free = 1;
	}
}

void	exec_comm(char *comm, t_envir *env)
{
	t_execord	exec_order;

	if (!comm || !comm[0])
		ft_putstr_fd("minishell: empty argument", 1);
	else
	{
		get_execord(comm, env->paths, &exec_order);
		if (!exec_order.comm)
		{
			ft_putstr_fd("minishell: ", 1);
			if (exec_order.free)
				ft_putstr_fd("command not found: ", 1);
			else
				ft_putstr_fd("file not found: ", 1);
			ft_putendl_fd(exec_order.argsum[0], 1);
		}
		else
			exec(&exec_order, env->envp);
		execfree(&exec_order);
	}
}
