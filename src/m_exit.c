/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:53:48 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/07 14:38:17 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_exit(t_envir *env)
{
	if (env->paths)
		free_array(env->paths);
	if (env->e_envp)
		free_array(env->e_envp);
	if (env->prompt)
		free(env->prompt);
	exit(0);
}
