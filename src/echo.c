/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:39:15 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/08 16:25:38 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv, int wfd)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (argv[1] && ft_strnstr(argv[1], "-n", 2) && !argv[1][2])
	{
		check = 1;
		i++;
	}
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], wfd);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', wfd);
		i++;
	}
	if (check == 0)
		ft_putchar_fd('\n', wfd);
	return (0);
}
