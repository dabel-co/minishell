/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:58:10 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 12:47:24 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		execord->err_msg = err_file(filename, strerror(errno))/*err_msg(filename)*/;
	free(filename);
	if (fd > 1)
	{
		last = search_op(&redir[2], redir[0]);
		if (last || (redir[0] == '<' && execord->in_fd))
			close(fd);
		else
			return (fd);
	}
	return (0);
}

// void	take_redir(char *redir, char **order, t_exec *execord)
// {
// 	int		start;
// 	int		ind;
// 	int		fd;
// 	char	*filename;

// 	ind = 0;
// 	while (redir[ind] == redir[0])
// 		ind++;
// 	while (redir[ind] == ' ')
// 		ind++;
// 	start = ind;
// 	while (redir[ind] && !ft_strchr("| <>", redir[ind]))
// 		ind++;
// 	filename = remove_quotes(ft_substr(redir, start, (ind - start)));
// 	fd = open_redir(redir, filename, execord);
// 	if (fd && redir[0] == '>')
// 		execord->out_fd = fd;
// 	else if (fd)
// 		execord->in_fd = fd;
// 	*order = ft_strcrop_free(*order, (redir - *order), ind);
// }

void	take_redir(char *redir, char **order, t_exec *execord, t_envir *env)
{
	int		fd;
	int		end;
	char	*filename;

	filename = remove_quotes(expand_line(take_keyword(redir, &end), env, '\0'));
	fd = open_redir(redir, filename, execord);
	if (fd && redir[0] == '>')
		execord->out_fd = fd;
	else if (fd)
		execord->in_fd = fd;
	*order = ft_strcrop_free(*order, (redir - *order), end);
}

// int	take_all_redir(char **order, t_exec *execord)
// {
// 	char	*redir;
// 	char	limiter;

// 	if (execord->err_msg)
// 		return(0);
// 	redir = *order;
// 	while (*redir && *redir != '<' && *redir != '>')
// 	{
// 		if (*redir == '\\')
// 			redir++;
// 		else if (*redir == '\'' || *redir == '\"')
// 		{
// 			limiter = *redir;
// 			redir++;
// 			while (*redir != limiter)
// 				redir++;
// 		}
// 		redir++;
// 	}
// 	if (!*redir)
// 		return (1);
// 	take_redir(redir, order, execord);
// 	return (take_all_redir(order, execord));
// }

int	take_all_redir(char **order, t_exec *execord, t_envir *env)
{
	char	*redir;
	char	limiter;

	if (execord->err_msg)
		return(0);
	redir = *order;
	while (*redir && *redir != '<' && *redir != '>')
	{
		if (*redir == '\'' || *redir == '\"')
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
	take_redir(redir, order, execord, env);
	return (take_all_redir(order, execord, env));
}
