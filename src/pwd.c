/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:40:19 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/26 17:06:24 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*dir;
	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putendl_fd(dir, STDOUT_FILENO);
	free(dir);
	return (0);
}
