/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:45:23 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/03 13:30:28 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path)
{
	chdir(path);
	return (0);
}

int	*ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putendl_fd(dir, STDOUT_FILENO);
	free(dir);
	return (0);
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
