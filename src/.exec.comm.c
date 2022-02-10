/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:14:39 by marvin            #+#    #+#             */
/*   Updated: 2022/01/31 15:06:08 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	exec(t_execord *execorder, t_envir *env)
{
	//send env stuff here and fix cd thingy
	if (ft_strnstr(execorder->argsum[0], "cd", 2) && !execorder->argsum[0][2])
		write(1, "a", 1);
	else if (ft_strnstr(execorder->argsum[0], "echo", 4) && !execorder->argsum[0][4])
		ft_echo(execorder->argsum);
	else if (ft_strnstr(execorder->argsum[0], "pwd", 3) && !execorder->argsum[0][3])
		ft_pwd();
	else if (execve(execorder->comm, execorder->argsum, env->e_envp) < 0)
		perror(execorder->argsum[0]);
	exit (0);
} */

void	set_exec(t_execord *execorder, t_envir *env)
{
	pid_t		pidC;

	pidC = fork();
	if (pidC == -1)
		perror("fork");
	else if (pidC == 0)
		exec(execorder, env);
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
		ft_putstr_fd("", 1);
	else
	{
		get_execord(comm, env->paths, &exec_order);
		if (!exec_order.comm)
		{
			ft_putstr_fd("Minishell: ", 1);
			if (exec_order.free)
				ft_putstr_fd("command not found: ", 1);
			else
				ft_putstr_fd("file not found: ", 1);
			ft_putendl_fd(exec_order.argsum[0], 1);
		}
		else
			set_exec(&exec_order, env);
		execfree(&exec_order);
	}
}