/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:19:58 by vguttenb          #+#    #+#             */
/*   Updated: 2022/01/21 11:49:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err_msg_out(char err)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putchar_fd(err, 1);
	ft_putendl_fd("'", 1);
	exit(0);
}

int	syntax_err_out(char *comm)
{
	int	ret;

	ret = 0;
	while(*comm)
	{
		if(*comm++ == '>')
		{
			ret++;
			if (*comm == '>')
				comm += 1;
			if (!*comm)
				syntax_err_msg_out(*comm);
			while(*comm == ' ')
				comm += 1;
			if (!*comm || *comm == '<' || *comm == '>' || *comm == '\n')
				syntax_err_msg_out(*comm);
		}
	}
	return (ret);
}

int	file_wr_fd(char *filename, int mode)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | mode, 0666);
	if (fd > 0)
		return (fd);
	perror("open");
	return(0);
	//salir por patas
}

int	take_output(char **comm, char *output)
{
	char	*filename;
	int		ind;
	int		start;
	int		fd;

	ind = 1;
	if (output[ind] == '>')
		ind++;
	while (output[ind] == ' ')
		ind++;
	start = ind;
	while (!ft_strchr(" <>", output[ind]))
		ind++;
	filename = ft_substr(output, start, (ind - start));
	if (output[1] == '>')
		fd = file_wr_fd(filename, O_APPEND);
	else/* if (!execord->ignore)*/
		fd = file_wr_fd(filename, O_TRUNC);
	free(filename);
	filename = ft_strcrop(*comm, (output - *comm), (&output[ind] - output));
	free(*comm);
	*comm = filename;
	return(fd);
}

int	take_all_output(char **comm, int old_fd)
{
	char	*last_output;
	char	*output;

	last_output = ft_strrchr(*comm, '>');
	if (last_output > *comm && *(last_output - sizeof(char)) == '<')
		last_output -= sizeof(char);
	output = ft_strchr(*comm, '>');
	if (output == last_output && old_fd == 0)
		return (take_output(comm, output));
	else if (output)
		close(take_output(comm, output));
	else
		return (old_fd);
	return (take_all_output(comm, old_fd));
}

int	output_redir(char **comm, int wfd/* estructura */)
{
	int		output_num;

	output_num = syntax_err_out(*comm);
	if (!output_num)
		return(wfd);
	if (wfd)
		close(wfd);
	wfd = take_all_output(comm, 0);
	return(wfd);
}