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

int	tty_in_fd(char *comm)
{
	char	*eof;
	
}

int	file_in_fd(char *comm)
{
	char	*filename;
	int		ind;
	int		first;
	int		fd;

	ind = 0;
	while(comm[ind] && comm[ind] == ' ')
		ind++;
	if (!comm[ind] || comm[ind] == '\n')
		return (0);
	first = ind;
	while(comm[ind] && comm[ind] != ' ')
		ind++;
	filename = ft_substr(comm, first, ind - first);
	fd = open(filename, O_RDONLY);
	if (fd > 0)
		return (fd)
	perror(open);
	return (null_fd());
}

char	*get_in_fd(char *comm, t_execord *exec_order, int rfd)
{
	char	*input;

	input = ft_strnstr(comm, "<", ft_strlen(comm));
	if (!input)
		return (comm);
	if (rfd)
		close (rfd);
	if (ft_strnstr(input, "<<", 2))
		exec_order->in_fd = tty_in_fd(input + sizeof(char) * 2);
	else
		exec_order->in_fd = file_in_fd(input + sizeof(char));
	if (!exec_order->in_fd)
		super_exit()
	comm = trim_input(comm);
	return (comm);
}

void	exec_pipe(char *comm, int rfd, int *pip)
{
	t_execord	exec_order;

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
