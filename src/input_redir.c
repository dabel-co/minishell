/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:20:14 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/10 15:14:01 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err_msg(char err)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putchar_fd(err, 1);
	ft_putendl_fd("'", 1);
	exit(0);
}

int	syntax_err(char *comm)
{
	int	ret;

	ret = 0;
	while(*comm)
	{
		if(*comm++ == '<')
		{
			ret++;
			if (*comm == '<')
				comm += 1;
			if (!*comm)
				syntax_err_msg(*comm);
			while(*comm == ' ')
				comm += 1;
			if (!*comm || *comm == '<' || *comm == '>' || *comm == '\n')
				syntax_err_msg(*comm);
		}
	}
	return (ret);
}

static int	tty_fd(char *limiter)
{
	int		pip[2];
	char	buffer[2];
	char	*keeper;

	pipe(pip);
	buffer[1] = '\0';
	while (1)
	{
		keeper = NULL;
		write(1, "> ", 2);
		while (!ft_strchr(keeper, '\n'))
		{
			read(0, &buffer[0], 1);
			keeper = ft_strjoin_free(keeper, buffer);
		}
		if (ft_strnstr(keeper, limiter, ft_strlen(limiter))
			&& keeper[ft_strlen(limiter)] == '\n')
			break ;
		write(pip[WR_END], keeper, ft_strlen(keeper));
		free (keeper);
	}
	free (keeper);
	close(pip[WR_END]);
	return (pip[RD_END]);
}

static int	null_fd(void)
{
	int	fd[2];

	pipe(fd);
	close(fd[WR_END]);
	return (fd[RD_END]);
}

int	file_rd_fd(char *filename/*, t_execord *exec_order*/)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd > 0/* && !exec_order->ignore_fd*/)
		return (fd);
	//exec_order->ignore = 1;
	perror("open");
	//free(filename);
	return (null_fd());
}

int		take_input(char **comm, char *input)
{
	char	*keyword;
	int		ind;
	int		start;
	int		fd;

	ind = 1;
	if (input[ind] == '<')
		ind++;
	while (input[ind] == ' ')
		ind++;
	start = ind;
	while (!ft_strchr(" <>", input[ind]))
		ind++;
	keyword = ft_substr(input, start, (ind - start));
	if (input[1] == '<')
		fd = tty_fd(keyword);
	else/* if (!execord->ignore)*/
		fd = file_rd_fd(keyword);
	/*ft_putendl_fd(*comm, 1);
	ft_putendl_fd(input, 1);
	ft_putendl_fd(keyword, 1);*/
	free(keyword);
	keyword = ft_strcrop(*comm, (input - *comm), (&input[ind] - input));
	free(*comm);
	*comm = keyword;
	/*ft_putendl_fd(*comm, 1);
	ft_putnbr_fd(fd, 1);
	ft_putchar_fd('\n', 1);*/
	return(fd);
}

int	take_all_input(char **comm, char *mode, int old_fd)
{
	char	*last_input;
	char	*input;

	last_input = ft_strrchr(*comm, '<');
	if (last_input > *comm && *(last_input - sizeof(char)) == '<')
		last_input -= sizeof(char);
	input = ft_strnstr(*comm, mode, ft_strlen(*comm));
	if (input == last_input && old_fd == 0)
		return (take_input(comm, input));
	else if (input)
		close(take_input(comm, input));
	else
		return (old_fd);
	return (take_all_input(comm, mode, old_fd));
}

int	input_redir(char **comm, int rfd, t_envir *env)
{
	int		input_num;
	
	input_num = syntax_err(*comm);
	if (!input_num)
		return(rfd);
	if (rfd)
		close(rfd);
	rfd = take_all_input(comm, "<<", 0);
	*comm = expand_line(*comm, env);
	rfd = take_all_input(comm, "<", rfd);
	return(rfd);
}
