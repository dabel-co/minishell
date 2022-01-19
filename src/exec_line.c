/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:14:37 by marvin            #+#    #+#             */
/*   Updated: 2022/01/03 17:14:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **to_print)
{
	while(*to_print)
		ft_putendl_fd(*to_print++, 1);
}

static int	get_tty(char *limiter)
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
		while (!sec_strchr(keeper, '\n'))
		{
			read(0, &buffer[0], 1);
			keeper = gnl_strjoin(keeper, buffer);
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

int	tty_in_fd(char *comm)
{
	char	*eof;

	int		ind;
	int		first;
	int		fd;

	ind = 0;
	while(comm[ind] && comm[ind] == ' ')
		ind++;
	if (!comm[ind] || comm[ind] == '\n' || comm[ind] == '<')
		return (0);
	first = ind;
	while(comm[ind] && comm[ind] != ' ')
		ind++;
	eof = ft_substr(comm, first, ind - first);
	fd = get_tty(eof);
	free(eof);
	return (fd);
}

int	file_in_fd(char *comm, t_execord *exec_order)
{
	char	*filename;
	int		ind;
	int		first;
	int		fd;

	ind = 0;
	while(comm[ind] && comm[ind] == ' ')
		ind++;
	if (!comm[ind] || comm[ind] == '\n')
		return (-1);
	first = ind;
	while(comm[ind] && comm[ind] != ' ')
		ind++;
	filename = ft_substr(comm, first, ind - first);
	fd = open(filename, O_RDONLY);
	if (fd > 0 && !exec_order->ignore_fd)
		return (fd)
	exec_order->ignore = 1;
	perror(open);
	free(filename);
	return (null_fd());
}

// char	*get_in_fd(char *comm, t_execord *exec_order, int rfd)
// {
// 	char	*input;

// 	input = ft_strnstr(comm, "<", ft_strlen(comm));
// 	if (!input)
// 		return (comm);
// 	if (rfd)
// 		close (rfd);
// 	if (ft_strnstr(input, "<<", 2))
// 		exec_order->in_fd = tty_in_fd(input + sizeof(char) * 2);
// 	else
// 		exec_order->in_fd = file_in_fd(input + sizeof(char));
// 	if (!exec_order->in_fd)
// 		super_exit()
// 	comm = trim_input(comm);
// 	return (comm);
// }

char	*get_in_fd(char *comm, t_execord *exec_order, int rfd)
{
	char	*f_input;
	char	*input;
	int		fd;

	if (ft_strnstr(comm, "<<<", 3))
		super_exit();
	f_input = strrchr(comm, '<');
	if (!f_input)
		return (rfd);
	if (f_input > comm && *(f_input - sizeof(char) == '<')
		f_input -= sizeof(char);
	input = ft_strnstr(comm, "<<", ft_strlen(comm));
	while(input && input < f_input)
	{
 		fd = tty_in_fd(input + sizeof(char) * 2);
		if (fd < 0)
			super_exit();
		close(fd):
		comm = trim_input(comm);
		input = ft_strnstr(comm, "<<", ft_strlen(comm));
	}
	
}

void	exec_pipe(char *comm, int rfd, int *pip)
{
	t_execord	exec_order;

	exec_order->ignore = 0;
	comm = get_in_fd(comm, &exec_order, rfd);
	comm = get_out_fd(comm, &exec_order, pip[WR_END]);

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
		exec_pipe(order[ind], pip[ind % 2 + 1][RD_END], pip[ind % 2])
		ind++;
	}
	exec_fd(order[ind], pip[ind % 2][RD_END])
}

void	exec_line(char *comm_line, t_envir *env)
{
	//t_execord	exec_order;
	char		**orders;
	int			pip[2][2];

	(void)env;
	if (!comm_line || !comm_line[0])
		ft_putstr_fd("", 1);
	else
	{
		orders = ft_split(comm_line, '|');
		exec_manage(orders);
		//print_array(orders);
	}
}
