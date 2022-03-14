/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:44:12 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/14 16:33:15 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec(t_exec *node, t_envir *env)
// {
// 	if (!execve(node->exec_path, node->argv, env->e_envp))
// 		perror(node->argv[0]);
// 	//system("leaks -q minishell");
// 	exit(0);
// }

int	exec_binode(t_exec *node, t_envir *env)
{
	if (node->argv)
	{
		if (ft_strcmp(node->argv[0], "cd"))
			return (ft_cd(node->argv[1], env));
		else if (ft_strcmp(node->argv[0], "export"))
			return (ft_export(env, node->argv[1], node->out_fd));
		else if (ft_strcmp(node->argv[0], "unset"))
			return (ft_unset(env, node->argv[1]));
		else if (ft_strcmp(node->argv[0], "echo"))
			return (ft_echo(node->argv, node->out_fd));
		else if (ft_strcmp(node->argv[0], "env"))
			return (ft_env(env->e_envp, 0, node->out_fd));
		else if (ft_strcmp(node->argv[0], "pwd"))
			return (ft_pwd(node->out_fd));
	}
	return (0);
}

int	exec_spnode(t_exec *node, t_envir *env)
{
	pid_t	pidC;

	pidC = fork();
	check_signal_mode(node->argv[0]);
	if (pidC == -1)
		ft_putendl_fd("error creando fork", 1); //TENEMOS QUE DISCUTIR QUÉ HACER EN ESTOS CASOS
	else if (pidC == 0)
	{
		//signal(SIGINT, SIG_DFL);
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
		if (!execve(node->exec_path, node->argv, env->e_envp))
			perror(node->argv[0]);
		system("leaks -q minishell");
		//pidC = -1; //ESTO NO VA A HACER NADA PORQUE ESTÁ EN EL PROCESO HIJO
		exit(0);
	}
	return (pidC);
}

int	set_pipe(t_exec *node)
{
	int		pip[2];
	
	if (pipe(pip) < 0)
	{
		ft_putendl_fd("error creando pipe", 1); //TENEMOS QUE DISCUTIR QUÉ HACER EN ESTOS CASOS
		close(pip[WR_END]);
		close(pip[RD_END]);
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

int	exec_list(t_exec *list, t_envir *env, int *subp_count)
{
	int		ret;
	t_exec	*next;
	
	//errno = 0;
	ret = 1;
	if (!list)
		return (0);
	if (list->next)
		set_pipe(list);
	if (list->err_msg)
		ft_putendl_fd(list->err_msg, STDERR_FILENO);
	else if (list->exec_path) //AQUÍ SERÍA INTERESANTE MODIFICARLO PARA QUE SI HAY UN ERROR CREANDO FORK LA COSA SALGA SIN PROBLEMA
	{
		ret = exec_spnode(list, env);
		*subp_count += 1; //SERÍA DESEABLE QUE ESTO NO OCURRA SI EXISTE ALGÚN FALLO
	}
	else 
		ret = exec_binode(list, env);
	next = list->next;
	free_node(list);
	if (next)
		return (exec_list(next, env, subp_count));
	return (ret);
}
