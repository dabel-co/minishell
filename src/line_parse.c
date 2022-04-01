/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:46:47 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/01 18:32:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*syntax_err(char problem)
{
	char	err_str[2];
	char	*ret;

	err_str[1] = '\0';
	err_str[0] = problem;
	if (problem == '\'' || problem == '\"')
		return (ft_strjoin(ERR_SYNT_Q, err_str));
	if (!problem)
		return (ft_strjoin(ERR_SYNT_T, "newline'"));
	ret = ft_strjoin(ERR_SYNT_T, err_str);
	return (ft_strjoin_free(ret, "'"));
}

static char	*check_quotes(char **line, int *ind)
{
	char	limiter;

	limiter = line[0][*ind];
	*ind += 1;
	while (line[0][*ind] && line[0][*ind] != limiter)
		*ind += 1;
	if (!line[0][*ind])
		return (syntax_err(limiter));
	*ind += 1;
	return (NULL);
}

static char	*check_pipe(char **line, int *ind)
{
	*ind += 1;
	while (line[0][*ind] && line[0][*ind] == ' ')
		*ind += 1;
	if (!line[0][*ind] || line[0][*ind] == '|')
		return (syntax_err(line[0][*ind]));
	return (NULL);
}

static char	*check_redir(char **line, int *ind)
{
	if (line[0][*ind] == line[0][*ind + 1])
		*ind += 1;
	*ind += 1;
	while (line[0][*ind] && line[0][*ind] == ' ')
		*ind += 1;
	if (!line[0][*ind] || ft_strchr("><|", line[0][*ind]))
		return (syntax_err(line[0][*ind]));
	return (NULL);
}

int	line_parse(char **line)
{
	int		ind;
	char	*err;

	ind = 0;
	err = NULL;
	if (ft_strnstr(*line, " ", ft_strlen(*line)))
		err = ft_strdup("minishell: syntax error near non-unicode character");
	while (line[0][ind] && !err)
	{
		if (line[0][ind] == '\'' || line[0][ind] == '\"')
			err = check_quotes(line, &ind);
		else if (line[0][ind] == '|')
			err = check_pipe(line, &ind);
		else if (line[0][ind] == '>' || line[0][ind] == '<')
			err = check_redir(line, &ind);
		else if (line[0][ind] > 8 && line[0][ind] < 14)
			line[0][ind++] = ' ';
		else
			ind++;
	}
	if (!err)
		return (1);
	ft_putendl_fd(err, 1);
	free(err);
	return (0);
}
