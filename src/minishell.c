/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:54:59 by marvin            #+#    #+#             */
/*   Updated: 2022/03/09 13:07:07 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_close(t_exec *execord)
{
	int	ind;

	ind = 1;
	while (execord)
	{
		ft_putstr_fd("Orden nº ", 1);
		ft_putnbr_fd(ind++, 1);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("path: ", 1);
		if (execord->exec_path)
			ft_putstr_fd(execord->exec_path, 1);
		ft_putchar_fd('\n', 1);
		ft_putendl_fd("args:", 1);
		if (execord->argv)
			while (*execord->argv)
			{	
				ft_putstr_fd(">:", 1);
				ft_putendl_fd(*execord->argv++, 1);
			}
		ft_putstr_fd("in_fd: ", 1);
		ft_putnbr_fd(execord->in_fd, 1);
		ft_putchar_fd('\n', 1);
		if (execord->in_fd)
			close(execord->in_fd);
		ft_putstr_fd("out_fd: ", 1);
		ft_putnbr_fd(execord->out_fd, 1);
		ft_putchar_fd('\n', 1);
		if (execord->out_fd)
			close(execord->out_fd);
		ft_putstr_fd("err_msg: ", 1);
		if (execord->err_msg)
			ft_putstr_fd(execord->err_msg, 1);
		ft_putchar_fd('\n', 1);
		ft_putchar_fd('\n', 1);
		execord = execord->next;
	}
}

void	waitpid_status_diagnose(int status)
{
	if (WIFEXITED(status))
	{
		ft_putstr_fd("El proceso ha salido con normalidad con código de salida: ", 1);
		ft_putnbr_fd(WEXITSTATUS(status), 1);
		ft_putchar_fd('\n', 1);
	}
	if (WIFSIGNALED(status))
		ft_putendl_fd("El proceso ha salido a causa de una señal", 1);
	if (WIFCONTINUED(status))
		ft_putendl_fd("El proceso ha salido a causa de una señal2", 1);
}

// void	readfromprompt(t_envir *env)
// {
// 	char	*new_comm;
// 	int		last_pid;
// 	int		subp_count;
// 	int		status;

// 	new_comm = readline("SUSSYBAKA@WEEABOSHELL$ ");
// 	if (!new_comm || ft_strcmp(new_comm, "exit"))
// 	{
// 		free(new_comm);
// 		rl_clear_history();
// 		ft_putstr_fd("exit\n", 1);
// 		exit(0);
// 	}
// 	if (line_parse(&new_comm))
// 	{
// 		g_err = 0;
// 		subp_count = 0;
// 		last_pid = exec_list(tokenizator(smart_split(new_comm, '|'), env), env, &subp_count);
// 		while (subp_count-- > 0)
// 		{
// 			//waitpid(-1, NULL, 0);
// 			if (waitpid(-1, &status, 0) == last_pid)
// 			{
// 				if (WIFEXITED(status))
// 					printf("WEXITSTATUS da como resultado: %d\n", WEXITSTATUS(status));
// 				else if (WIFSIGNALED(status))
// 					printf("WTERMSIG da como resultado: %d\n", WTERMSIG(status));
// 				// printf("errno es %d ahora mismo y significa %s\n", errno, strerror(errno));
// 				// printf("EINTR es %d ahora mismo\n", EINTR);
// 				// ft_putnbr_fd(WEXITSTATUS(status), STDOUT_FILENO);
// 				// ft_putnbr_fd(WTERMSIG(status), STDOUT_FILENO);
// 			}
// 		}
// 		if (last_pid < 2)
// 			printf("El último proceso salió con %d\n", last_pid);
// 	}
// 	add_history(new_comm);
// 	free(new_comm);
// }

// void	update_underscore(char *line, t_envir *env)
// {
// 	int		ind;
// 	char	*last_arg;

// 	ind = ft_strlen(line) - 1;
// 	while (ind > 0 && line[ind] == ' ')
// 		ind--;
// 	while (ind > 0 && line[ind] != ' ')
// 		ind--;
// 	last_arg = ft_strtrim(&line[ind], " ");
// 	ft_putendl_fd(last_arg, STDERR_FILENO);
// 	env_home_export(ft_strjoin("_=", last_arg), env, 1);
// 	free(last_arg);
// }

void	readfromprompt(t_envir *env)
{
	char	*new_comm;
	//int		subp_count;

	new_comm = readline("SUSSYBAKA@WEEABOSHELL$ ");
	if (!new_comm || ft_strcmp(new_comm, "exit"))
	{
		free(new_comm);
		rl_clear_history();
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	g_err = 0;
	if (line_parse(&new_comm))
	{
		//subp_count = 0;
		exec_list(tokenizator(smart_split(new_comm, '|'), env), env, 0);
	}
	if (new_comm[0])
		add_history(new_comm);
	//update_underscore(new_comm, env);
	free(new_comm);
}

void	readfromfile(t_envir *env)
{
	int		nbytes;
	int		last_pid;
	char	*new_comm;

	ioctl(STDIN_FILENO, FIONREAD, &nbytes);
	while (nbytes)
	{
		new_comm = readline(NULL);
		if (ft_strcmp(new_comm, "exit"))
		{
			free(new_comm);
			exit(0);
		}
		if (line_parse(&new_comm))
		{
			g_err = 0;
			last_pid = exec_list(tokenizator(smart_split(new_comm, '|'), env), env, 0);
		}
		free(new_comm);
		ioctl(STDIN_FILENO, FIONREAD, &nbytes);
	}
}

void	hola()
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_envir	env;

	(void)argc;
	(void)argv;
	check_signal_mode(0);
	// signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	env.e_envp = get_env(envp);
	if (!check_path(&env))
		env.paths = get_paths(envp);
	else
		env.paths = check_path(&env);
	update_shlvl(&env);
	//atexit(hola);
	if (isatty(STDIN_FILENO))
		while (1)
			readfromprompt(&env);
	else
		readfromfile(&env);
}
