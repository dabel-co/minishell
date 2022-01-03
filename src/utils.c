/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:45:23 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/03 12:46:54 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	//getcwd allocates memory, will need to free this later outside
	return (dir);
}

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
