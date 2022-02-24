/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:44:12 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/24 17:22:50 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_exec *node, t_envir *env)
{
	if (node->exec_path && !execve(node->exec_path, node->argv, env->e_envp))
		perror(node->argv[0]);
	else if (ft_strcmp(node->argv[0], "echo"))
		ft_echo(node->argv);
	else if (ft_strcmp(node->argv[0], "env"))
		ft_env(env->e_envp, 0);
	else if (ft_strcmp(node->argv[0], "pwd"))
		ft_pwd();
	exit(0);
}

void	exec_binode(t_exec *node, t_envir *env)
{
	if (ft_strcmp(node->argv[0], "cd"))
		ft_cd(node->argv[1], env);
	else if (ft_strcmp(node->argv[0], "export"))
		ft_export(env, node->argv[1]);
	else if (ft_strcmp(node->argv[0], "unset"))
		ft_unset(env, node->argv[1]);
}

void	exec_spnode(t_exec *node, t_envir *env)
{
	pid_t	pidC;

	pidC = fork();
	if (pidC == -1)
		ft_putendl_fd("error creando fork", 1); //TENEMOS QUE DISCUTIR QUÉ HACER EN ESTOS CASOS
	else if (pidC == 0)
	{
		if (node->in_fd)
		{
			dup2(node->in_fd, STDIN_FILENO);
			close(node->in_fd);
		}
		else
			close(STDIN_FILENO);
		if (node->out_fd)
		{
			dup2(node->out_fd, STDOUT_FILENO);
			close(node->out_fd);
		}
		else if (node->next)
			close(STDOUT_FILENO);
		exec(node, env);
	}
}

void	free_node(t_exec *node)
{
	char	**to_free;

	if (node->in_fd)
		close(node->in_fd);
	if (node->out_fd)
		close(node->out_fd);
	if (node->exec_path)
		free(node->exec_path);
	if (node->argv)
	{
		to_free = node->argv;
		while (*node->argv)
			free(*node->argv++);
		free(to_free);
	}
	if (node->err_msg)
		free(node->err_msg);
	free(node);
	
}

int	exec_list(t_exec *list, t_envir *env, int subp_count)
{
	int		pip[2];
	t_exec	*next;

	if (!list)
		return (subp_count);
	if (list->err_msg)
		ft_putendl_fd(list->err_msg, 1);
	else if (!list->exec_path)
		exec_binode(list, env);
	else
	{
		if (!list->out_fd && list->next)
		{
			if (pipe(pip) < 0)
				ft_putendl_fd("error creando pipe", 1); //TENEMOS QUE DISCUTIR QUÉ HACER EN ESTOS CASOS
			list->out_fd = pip[WR_END];
			if (list->next->in_fd)
				close(list->next->in_fd);
			list->next->in_fd = pip[RD_END];
		}
		subp_count++;
		exec_spnode(list, env);
	}
	next = list->next;
	free_node(list);
	return (exec_list(next, env, subp_count));
}