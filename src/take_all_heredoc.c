/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:52:30 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 17:09:59 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rdline_hdoc(int wfd, char *eof, t_envir *env)
{
	char	*keeper;
	char	qtd_mode;

	qtd_mode = 0;
	signal(SIGINT, handle_signals_heredoc);
	if (ft_strchr(eof, '\'') || ft_strchr(eof, '\"'))
	{
		qtd_mode++;
		eof = remove_quotes(eof);
	}
	while (1)
	{
		keeper = readline("> ");
		if (!keeper || ft_strcmp(keeper, eof) || g_err == 1)
			break ;
		if (!qtd_mode)
			keeper = expand_line(keeper, env, 10);
		write(wfd, keeper, ft_strlen(keeper));
		write(wfd, "\n", 1);
		free(keeper);
	}
	free(keeper);
	free(eof);
	signal(SIGINT, handle_signals);
}

static int	take_heredoc(char **comm, char *input, t_envir *env)
{
	char	*keyword;
	int		end;
	int		pip[2];

	keyword = take_keyword(input, &end);
	if (pipe(pip) < 0)
	{
		perror("minishell: pipe");
		return (0);
	}
	rdline_hdoc(pip[WR_END], keyword, env);
	if (search_op(&input[2], '<') || g_err == 1)
	{
		close(pip[RD_END]);
		pip[RD_END] = 0;
	}
	*comm = ft_strcrop_free(*comm, (input - *comm), end);
	close(pip[WR_END]);
	return (pip[RD_END]);
}

int	take_all_heredoc(char **comm, t_envir *env)
{
	char	*input;
	char	limiter;
	int		fd;

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
	if (!*input)
		return (0);
	fd = take_heredoc(comm, input, env);
	if (fd != 0 || g_err == 1)
		return (fd);
	return (take_all_heredoc(comm, env));
}
