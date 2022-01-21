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

void	exec(t_execord *execorder, t_envir *env)
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
}

void	set_exec(t_execord *execorder, t_envir *env, int rfd, int *pip)
{
	pid_t		pidC;

	pidC = fork();
	if (pidC == -1)
		perror("fork");
	else if (pidC == 0)
	{
		if (pip[RD_END] > 1)
			close(pip[RD_END]);
		dup2(rfd, STDIN_FILENO);
		if (rfd > 1)
			close(rfd);
		dup2(pip[WR_END], STDOUT_FILENO);
		if (pip[WR_END] > 1)
			close(pip[WR_END]);
		exec(execorder, env);
	}
	else
		waitpid(pidC, NULL, 0);
}

void	exec_pipe(char *comm, t_envir *env, int rfd, int *pip)
{
	t_execord	exec_order;

	exec_order.ignore = 0;
	rfd = input_redir(&comm, rfd/*, &exec_order*/);
	pip[WR_END] = output_redir(&comm, pip[WR_END]);
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
		set_exec(&exec_order, env, rfd, pip);
	execfree(&exec_order);
	if (rfd > 1)
		close(rfd);
	if (pip[WR_END] > 1)
		close(pip[WR_END]);
}

void	exec_manage(char **orders, t_envir *env)
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
		exec_pipe(orders[ind], env, pip[ind % 2 + 1][RD_END], pip[ind % 2]);
		ind++;
	}
	pip[ind % 2][WR_END] = 1;
	pip[ind % 2][RD_END] = 0;
	exec_pipe(orders[ind], env, pip[ind % 2 + 1][RD_END], pip[ind % 2]);
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
		exec_manage(orders, env);
		//print_array(orders);
	}
}
