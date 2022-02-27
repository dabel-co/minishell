/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:39:15 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/27 18:21:03 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
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
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (check == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
