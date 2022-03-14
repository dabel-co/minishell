/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:40:19 by dabel-co          #+#    #+#             */
/*   Updated: 2022/03/14 16:48:13 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int wfd)
{
	char	*dir;
 
	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl_fd(dir, wfd);
	free(dir);
	return (0);
}
