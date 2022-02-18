/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:58:10 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/17 20:26:37 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizator.h"

int	open_redir(char *redir, char *filename, t_exec *execord)
{
	int 	flags;
	int		fd;
	char	*last;

	if (redir[0] == '>' && redir[1] == '>')
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (redir[0] == '>')
		flags = O_WRONLY | O_CREAT | O_CREAT;
	else
		flags = O_RDONLY;
	fd = open(filename, flags, 0666);
	if (fd < 0)
		execord->err_msg = "problemas abriendo el archivo"/*err_msg(filename)*/;
	free(filename);
	if (fd > 1)
	{
		last = ft_strrchr(redir, redir[0]);
		if (redir[0] == '>' && last > redir && *(last - sizeof(char)) == '>')
			last -= sizeof(char);
		if (redir < last || (redir[0] == '<' && execord->in_fd))
			close(fd);
		else
			return (fd);
	}
	return (0);
}

void	take_redir(char *redir, char **order, t_exec *execord)
{
	int		start;
	int		ind;
	int		fd;
	char	*to_free;

	ind = 0;
	while (redir[ind] == redir[0])
		ind++;
	while (redir[ind] == ' ')
		ind++;
	start = ind;
	while (redir[ind] == !ft_strchr(" <>", redir[ind]))
		ind++;
	fd = open_redir(redir, ft_substr(redir, start, (ind - start)), execord);
	if (fd && redir[0] == '>')
		execord->out_fd = fd;
	else if (fd)
		execord->in_fd = fd;
	to_free = *order;
	*order = ft_strcrop_free(*order, (redir - *order), ind);
	free(to_free);
}

int	take_all_redir(char **order, t_exec *execord)
{
	char	*redir;
	char	limiter;

	if (execord->err_msg)
		return(0);
	redir = *order;
	while (*redir && *redir != '<' && *redir != '>')
	{
		if (*redir == '\\')
			redir++;
		else if (*redir == '\'' || *redir == '\"')
		{
			limiter = *redir;
			redir++;
			while (*redir != limiter)
				redir++;
		}
		redir++;
	}
	if (!*redir)
		return (1);
	take_redir(redir, order, execord);
	return (take_all_redir(order, execord));
}
