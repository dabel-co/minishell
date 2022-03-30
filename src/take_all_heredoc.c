/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:52:30 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/30 20:09:26 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*hdoc_nl()
// {
// 	char	buffer[2];
// 	char	*ret;

// 	buffer[1] = '\0';
// 	while (1)
// 	{
// 		ret = NULL;
// 		write(1, "> ", 2);
// 		while (read(0, &buffer[0], 1))
// 		{
// 			//read(0, &buffer[0], 1);
// 			ret = ft_strjoin_free(ret, buffer);
// 			if (buffer[0] == '\n' || g_err == 1)
// 				break ;
// 		}
// 		if (!ret)
// 			break ;	
// 	}
// 	return (ret);
// }

// void	sp_hdoc(int wfd, char *eof)
// {
// 	pid_t	pidC;
// 	char	*new_line;

// 	new_line = NULL;
// 	eof = ft_strjoin(eof, "\n");
// 	check_signal_mode("heredoc");
// 	pidC = fork();
// 	if (pidC == -1)
// 		ft_putendl_fd("problema creando el subproceso", 1);
// 	else if (pidC == 0)
// 	{
// 		while (1)
// 		{
// 			new_line = hdoc_nl();
// 			if (!new_line || ft_strcmp(new_line, eof) || g_err == 1)
// 				exit(g_err);
// 			write(wfd, new_line, ft_strlen(new_line));
// 			//write(wfd, "\n", 1);
// 			free(new_line);
// 		}
// 	}
// 	else
// 	{
// 		if (new_line)
// 			free(new_line);	
// 	}
// }

// void	hdoc_wr_fd(int wfd, char *eof)
// {
// 	pid_t	pidC;

// 	char	*new_line;
// 	eof = ft_strjoin(eof, "\n");
// 	check_signal_mode("heredoc");
// 	pidC = fork();
	
// 	while (1)
// 	{
// 		new_line = hdoc_nl();
// 		if (!new_line || ft_strcmp(new_line, eof) || g_err == 1)
// 			break ;
// 		write(wfd, new_line, ft_strlen(new_line));
// 		//write(wfd, "\n", 1);
// 		free(new_line);
// 	}
// 	if (new_line)
// 		free(new_line);
// }

// void	hdoc_wr_fd(int wfd, char *eof)
// {
// 	char	buffer[2];
// 	char	*keeper;

// 	eof = ft_strjoin(eof, "\n");
// 	buffer[1] = '\0';
// 	//check_signal_mode("heredoc");
// 	while (1)
// 	{
// 		keeper = NULL;
// 		write(1, "> ", 2);
// 		while (read(0, &buffer[0], 1))
// 		{
// 			//read(0, &buffer[0], 1);
// 			keeper = ft_strjoin_free(keeper, buffer);
// 			if (ft_strrchr(keeper, '\n') || g_err == 1)
// 				break ;
// 		}
// 		if (!keeper || ft_strcmp(keeper, eof) || g_err == 1)
// 			break ;
// 		write(wfd, keeper, ft_strlen(keeper));
// 		//write(wfd, "\n", 1);
// 		free(keeper);
// 	}
// 	if (keeper)
// 		free(keeper);
// }

char	*in_quote(char *str, char *quoting)
{
	char	*ret;
	
	if (quoting)
	{
		ret = ft_strjoin(quoting, str);
		ret = ft_strjoin_free(ret, quoting);
		free(str);
		return (ret);
	}
	str[ft_strlen(str) - 1] = '\0';
	ret = ft_strdup(str + 1);
	free(str);
	return(ret);
}

static void	rdline_hdoc(int wfd, char *eof, t_envir *env)
{
	char	*keeper;
	char	qtd_mode;

	qtd_mode = 0;
	check_signal_mode(2);
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
			// keeper = expand_line(keeper, env);
			keeper = in_quote(expand_line(in_quote(keeper, "\""), env), NULL);
		write(wfd, keeper, ft_strlen(keeper));
		write(wfd, "\n", 1);
		free(keeper);
	}
	free(keeper);
	free(eof);
	check_signal_mode(0);
}

// static void	rdline_hdoc(int wfd, char *eof)
// {
// 	char	*keeper;

// 	while (1)
// 	{
// 		check_signal_mode("eof");
// 		keeper = readline("> ");
// 		if (ft_strcmp(keeper, eof))
// 			break ;
// 		write(wfd, keeper, ft_strlen(keeper));
// 		write(wfd, "\n", 1);
// 		free(keeper);
// 	}
// 	free(keeper);
// 	return(1);
// }

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

int     take_heredoc(char **comm, char *input, t_envir *env)
{
	char    *keyword;
	int     end;
	int		pip[2];

	keyword = take_keyword(input, &end);
	if (pipe(pip) < 0)
		ft_putendl_fd("error creando pipe", 1); //EN ESTE CASO HABRÍA QUE CERRAR EL EXTREMO DE LECTURA Y DEVOLVER -1 PODRÍAMOS REDEFINIR EL EXTREMO DE LECTURA COMO -1 PARA QUE LA FUNCIÓN SIGA SU CURSO
	rdline_hdoc(pip[WR_END], keyword, env);
	if (search_op(&input[2], '<') || g_err == 1) //AQUÍ PODEMOS RECONVERTIR A 0 EL RD END
	{
		close(pip[RD_END]);
		pip[RD_END] = 0;
	}
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

int take_all_heredoc(char **comm, t_envir *env)
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
