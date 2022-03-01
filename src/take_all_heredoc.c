/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:52:30 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/01 16:31:26 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int     take_heredoc(char **comm, char *input)
// {
// 	char    *keyword;
// 	int     ind;
// 	int     start;
// 	int     fd;

// 	ind = 1;
// 	if (input[ind] == '<')
// 		ind++;
// 	while (input[ind] == ' ')
// 		ind++;
// 	start = ind;
// 	while (!ft_strchr("| <>", input[ind]))
// 		ind++;
// 	keyword = remove_quotes(ft_substr(input, start, (ind - start)));
// 	fd = tty_fd(keyword);
// 	free(keyword);
// 	*comm = ft_strcrop_free(*comm, (input - *comm), ind);
// 	return(fd);
// }

int     take_heredoc(char **comm, char *input)
{
	char    *keyword;
	int     end;
	int     fd;

	keyword = remove_quotes(take_keyword(input, &end));
	fd = tty_fd(keyword);
	free(keyword);
	*comm = ft_strcrop_free(*comm, (input - *comm), end);
	return(fd);
}

// int take_all_heredoc(char **comm)
// {
//     char    *last_input;
//     char    *input;

//     last_input = ft_strrchr(*comm, '<');
//     if (last_input > *comm && *(last_input - sizeof(char)) == '<')
//         last_input -= sizeof(char);
//     input = ft_strnstr(*comm, "<<", ft_strlen(*comm));
//     if (input && input == last_input)
//         return (take_heredoc(comm, input));
//     else if (input)
//         close(take_heredoc(comm, input));
//     else
//         return (0);
//     return (take_all_heredoc(comm));
// }

int take_all_heredoc(char **comm)
{
	char	*input;
	char	limiter;

	input = *comm;
	while (*input && !ft_strnstr(input, "<<", 2))
	{
		if (*input == '\'' || *input == '\"')
		{
			limiter = *input;
			input++;
			while (*input != limiter)
				input++;
		}
		input++;
	}
	if (*input && !search_op(&input[2], '<'))
		return (take_heredoc(comm, input));
	else if (*input)
		close(take_heredoc(comm, input));
	else
		return (0);
	return (take_all_heredoc(comm));
}
