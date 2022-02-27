/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:03:44 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/27 19:47:04 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals_subprocess(int sig)
{
	if (sig == 2)
		printf("control-c working in pwd\n");
}
void	handle_signals(int sig)
{
	if (sig == 2)
		printf("control-c\n");
}
