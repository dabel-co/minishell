/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:03:44 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/23 13:29:43 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_subprocess(int sig)
{
	if (sig == 2)
	{
		// write(1, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	if (sig == 3)
	{
		ft_putendl_fd("Sí he sido yo", STDERR_FILENO);
		//magia CORE DUMPEADO COMO UN DMPLING DE
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

// void	handle_sigquit(int sig)
// {
// 	if (sig == 3)
// 		kill(0, SIGQUIT);
// }

void	handle_signals(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// if (sig == 3)
	// 	rl_redisplay();
}

void	check_signal_mode(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, handle_signals);
		// signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, handle_signals_heredoc);
		// signal(SIGQUIT, SIG_IGN);
	}
}
