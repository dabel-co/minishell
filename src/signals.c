/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:03:44 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/04 19:37:46 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_subprocess(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		

	}
}

void	handle_signals_heredoc(int sig)
{
	//ft_putendl_fd((char *)rl_library_version, 1);
	if (sig == 2)
	{
		g_err = 1;
		//rl_done = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

void	check_signal_mode(char *str)
{
	//printf("a ver %s\n", str);
	if (ft_strcmp(str, "minishell"))
	{
		//printf("lol\n");
		signal(SIGINT, handle_signals);
	}
	else if (ft_strcmp(str, "subprocess"))
	{
		signal(SIGINT, handle_signals_subprocess);
	}
	else if (ft_strcmp(str, "heredoc"))
	{
		signal(SIGINT, handle_signals_heredoc);
	}
}
void	handle_signals(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
