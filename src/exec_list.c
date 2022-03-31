/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:44:12 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 18:42:09 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_binode(t_exec *node, t_envir *env)
{
	if (node->argv)
	{
		if (ft_strcmp(node->argv[0], "cd"))
			return (ft_cd(node->argv[1], env));
		else if (ft_strcmp(node->argv[0], "export"))
			return (ft_export(env, node->argv));
		else if (ft_strcmp(node->argv[0], "unset"))
			return (ft_unset(env, node->argv));
		else if (ft_strcmp(node->argv[0], "echo"))
			return (ft_echo(node->argv, node->out_fd));
		else if (ft_strcmp(node->argv[0], "env"))
			return (ft_env(env->e_envp, node->out_fd));
		else if (ft_strcmp(node->argv[0], "pwd"))
			return (ft_pwd(node->out_fd));
	}
	return (0);
}

static int	exec_spnode(t_exec *node, t_envir *env, int *subp_count)
{
	pid_t	pidc;

	signal(SIGINT, SIG_IGN);
	pidc = fork();
	if (pidc == -1)
		perror("minishell: fork");
	else if (pidc == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (node->next)
			close(node->next->in_fd);
		if (node->in_fd && dup2(node->in_fd, STDIN_FILENO) != -1)
			close(node->in_fd);
		if (node->out_fd && node->out_fd != STDOUT_FILENO && \
			dup2(node->out_fd, STDOUT_FILENO) != -1)
			close(node->out_fd);
		if (!execve(node->exec_path, node->argv, env->e_envp))
			perror(node->argv[0]);
		exit(0);
	}
	else
		*subp_count += 1;
	return (pidc);
}

static int	set_pipe(t_exec *node)
{
	int		pip[2];

	if (pipe(pip) < 0)
	{
		perror("minishell: pipe");
		return (0);
	}
	if (!node->out_fd)
		node->out_fd = pip[WR_END];
	else
		close(pip[WR_END]);
	if (node->next->in_fd)
		close(node->next->in_fd);
	node->next->in_fd = pip[RD_END];
	return (1);
}

static int	subp_wait(int subp_count, int last_pid, t_envir *env)
{
	int		status;

	while (subp_count-- > 0)
	{
		if (waitpid(-1, &status, 0) == last_pid)
		{
			if (WIFEXITED(status))
				env->zyzz = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 2)
					env->zyzz = 130;
				else if (WTERMSIG(status) == 3)
					env->zyzz = 131;
			}
		}
	}
	if (last_pid < 2)
		env->zyzz = last_pid;
	signal(SIGINT, handle_signals);
	return (1);
}

int	exec_list(t_exec *list, t_envir *env, int subp_count)
{
	int		ret;
	t_exec	*next;

	ret = 1;
	if (!list)
		return (subp_wait(0, 1, env));
	if (list->next)
		set_pipe(list);
	else if (!list->out_fd)
		list->out_fd = STDOUT_FILENO;
	if (list->err_msg)
		ft_putendl_fd(list->err_msg, STDERR_FILENO);
	else if (list->exec_path)
		ret = exec_spnode(list, env, &subp_count);
	else
		ret = exec_binode(list, env);
	next = list->next;
	free_node(list);
	if (next && ret == -1)
		free_list(next);
	else if (next)
		return (exec_list(next, env, subp_count));
	return (subp_wait(subp_count, ret, env));
}
