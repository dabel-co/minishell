/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:52:30 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/02 16:36:23 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hdoc_wr_fd(int wfd, char *eof)
{
	char	buffer[2];
	char	*keeper;

	buffer[1] = '\0';
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
		if (ft_strcmp(keeper, eof))
			break ;
		write(wfd, keeper, ft_strlen(keeper));
		write(wfd, "\n", 1);
		free (keeper);
	}
	free (keeper);
	return (1);
}

// static int	tty_fd(char *limiter)
// {
// 	int		pip[2];
// 	char	buffer[2];
// 	char	*keeper;

// 	pipe(pip);
// 	buffer[1] = '\0';
// 	while (1)
// 	{
// 		keeper = NULL;
// 		write(1, "> ", 2);
// 		while (!ft_strchr(keeper, '\n'))
// 		{
// 			read(0, &buffer[0], 1);
// 			keeper = ft_strjoin_free(keeper, buffer);
// 		}
// 		if (ft_strnstr(keeper, limiter, ft_strlen(limiter))
// 			&& keeper[ft_strlen(limiter)] == '\n')
// 			break ;
// 		write(pip[WR_END], keeper, ft_strlen(keeper));
// 		free (keeper);
// 	}
// 	free (keeper);
// 	close(pip[WR_END]);
// 	return (pip[RD_END]);
// }

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
	int		pip[2];

	keyword = remove_quotes(take_keyword(input, &end));
	if (pipe(pip) < 0)
		ft_putendl_fd("error creando pipe", 1); //EN ESTE CASO HABRÍA QUE CERRAR EL EXTREMO DE LECTURA Y DEVOLVER -1 PODRÍAMOS REDEFINIR EL EXTREMO DE LECTURA COMO -1 PARA QUE LA FUNCIÓN SIGA SU CURSO
	else if (!hdoc_wr_fd(pip[WR_END], keyword))
		ft_putendl_fd("error escribiendo en pipe", 1); //AQUÍ PODEMOS IMPLEMENTAR EL SISTEMA DE SEÑALES
	free(keyword);
	if (search_op(&input[2], '<')) //AQUÍ PODEMOS RECONVERTIR A 0 EL RD END
		close(pip[RD_END]);
	*comm = ft_strcrop_free(*comm, (input - *comm), end);
	close(pip[WR_END]);
	return (pip[RD_END]);
}

// int     take_heredoc(char **comm, char *input)
// {
// 	char    *keyword;
// 	int     end;
// 	int     fd;

// 	keyword = remove_quotes(take_keyword(input, &end));
// 	fd = tty_fd(keyword);
// 	free(keyword);
// 	*comm = ft_strcrop_free(*comm, (input - *comm), end);
// 	return(fd);
// }

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
	fd = take_heredoc(comm, input);
	if (fd != 0)
		return (fd);
	return (take_all_heredoc(comm));
}
