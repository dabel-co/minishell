/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:46:47 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/01 18:42:21 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sp_tty()
{
	char	buffer[2];
	char	*keeper;
	char	*iter;
	char	*ret;

	buffer[1] = '\0';
	ret = NULL;
	while (1)
	{
		keeper = NULL;
		write(1, "> ", 2);
		while (1)
		{
			read(0, &buffer[0], 1);
			if (buffer[0] == '\n')
				break ;
			keeper = ft_strjoin_free(keeper, buffer);
		}
		ret = ft_strjoin_free(ret, keeper);
		iter = keeper;
		while (*iter && *iter == ' ')
			iter++;
		if (*iter)
			break;
		if (keeper)
			free(keeper);
	}
	if (keeper)
		free(keeper);
	return (ret);
}

char	*syntax_err(char problem)
{
	char	err_str[2];
	char	*syntax;

	syntax = "minishell: syntax error near "; //ESTO HAY QUE CONVERTIRLO EN UN MACRO
	err_str[1] = '\0';
	err_str[0] = problem;
	if (problem == '\'' || problem == '\"')
	{
		syntax = ft_strjoin(syntax, "unclosed quotes: ");
		return (ft_strjoin_free(syntax, err_str));
	}
	syntax = ft_strjoin(syntax, "unexpected token: `");
	if (!problem)
		return (ft_strjoin_free(syntax, "newline'"));
	syntax = ft_strjoin_free(syntax, err_str);
	return (ft_strjoin_free(syntax, "'"));
}

char	*check_quotes(char **line, int *ind)
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

char	*check_pipe(char **line, int *ind)
{
	char	*err;
	
	err = NULL;
	*ind += 1;
	while (line[0][*ind] && line[0][*ind] == ' ')
		*ind += 1;
	if (!line[0][*ind])
	{
		err = sp_tty();
		*line = ft_strjoin_free(*line, err);
		free(err);
		err = NULL;
		while (line[0][*ind] && line[0][*ind] == ' ')
			*ind += 1;
	}
	if (!line[0][*ind] || line[0][*ind] == '|')
		return (syntax_err(line[0][*ind]));
	return (NULL);
}

char	*check_redir(char **line, int *ind)
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
	while (line[0][ind] && !err)
	{
		if (line[0][ind] == '\'' || line[0][ind] == '\"')
			err = check_quotes(line, &ind);
		else if (line[0][ind] == '|')
			err = check_pipe(line, &ind);
		else if (line[0][ind] == '>' || line[0][ind] == '<')
			err = check_redir(line, &ind);
		else
			ind++;
	}
	if (!err)
		return (1);
	ft_putendl_fd(err, 1);
	free(err);
	return (0);
}