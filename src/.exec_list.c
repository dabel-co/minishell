/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:44:12 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/10 16:13:59 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_exec *node, t_envir *env)
{
	if (!execve(node->exec_path, node->argv, env->e_envp))
		perror(node->argv[0]);
	//system("leaks -q minishell");
	exit(0);
}

void	exec_binode(t_exec *node, t_envir *env)
{
	if (node->argv)
	{
		if (ft_strcmp(node->argv[0], "cd"))
			ft_cd(node->argv[1], env);
		else if (ft_strcmp(node->argv[0], "export"))
			ft_export(env, node->argv[1], node->out_fd);
		else if (ft_strcmp(node->argv[0], "unset"))
			ft_unset(env, node->argv[1]);
		else if (ft_strcmp(node->argv[0], "echo"))
			ft_echo(node->argv, node->out_fd);
		else if (ft_strcmp(node->argv[0], "env"))
			ft_env(env->e_envp, 0, node->out_fd);
		else if (ft_strcmp(node->argv[0], "pwd"))
			ft_pwd(node->out_fd);
	}
}

void	exec_spnode(t_exec *node, t_envir *env, pid_t *last_pid)
{
	pid_t	pidC;

	pidC = fork();
	check_signal_mode(node->argv[0]);
	if (pidC == -1)
		ft_putendl_fd("error creando fork", 1); //TENEMOS QUE DISCUTIR QUÉ HACER EN ESTOS CASOS
	else if (pidC == 0)
	{
		if (node->in_fd)
		{
			dup2(node->in_fd, STDIN_FILENO);
			close(node->in_fd);
		}
		if (node->out_fd)
		{
			dup2(node->out_fd, STDOUT_FILENO);
			close(node->out_fd);
		}
		exec(node, env);
	}
	else if (!node->next)
		*last_pid = pidC;
}

int	exec_list(t_exec *list, t_envir *env, int subp_count, pid_t *last_pid)
{
	int		pip[2];
	t_exec	*next;
	
	//errno = 0;
	if (!list)
		return (subp_count);
	if (list->next)
	{
		if (pipe(pip) < 0)
			ft_putendl_fd("error creando pipe", 1); //TENEMOS QUE DISCUTIR QUÉ HACER EN ESTOS CASOS
		if (!list->out_fd)
			list->out_fd = pip[WR_END];
		else
			close(pip[WR_END]);
		if (list->next->in_fd)
			close(list->next->in_fd);
		list->next->in_fd = pip[RD_END];
	}
	if (list->err_msg)
		ft_putendl_fd(list->err_msg, STDERR_FILENO);
	else if (!list->exec_path)
		exec_binode(list, env);
	else //AQUÍ SERÍA INTERESANTE MODIFICARLO PARA QUE SI HAY UN ERROR CREANDO FORK LA COSA SALGA SIN PROBLEMA
	{
		subp_count++;
		exec_spnode(list, env, last_pid);
	}
	next = list->next;
	free_node(list);
	return (exec_list(next, env, subp_count, last_pid));
}
