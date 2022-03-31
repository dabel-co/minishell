/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:03:44 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/31 16:12:26 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_heredoc(int sig)
{
	if (sig == 2)
	{
		g_err = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
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

// void	check_signal_mode(int mode)
// {
// 	if (mode == 0)
// 		signal(SIGINT, handle_signals);
// 	else if (mode == 1)
// 		signal(SIGINT, SIG_IGN);
// 	else if (mode == 2)
// 		signal(SIGINT, handle_signals_heredoc);
// }
