/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:36:37 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/07 11:53:52 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	home_export(char *new_var, t_envir *env, int free_flag)
{
	char	*to_export[3];

	to_export[0] = NULL;
	to_export[1] = ft_strdup(new_var);
	to_export[2] = NULL;
	ft_export(env, to_export);
	free(to_export[1]);
	if (free_flag)
		free(new_var);
}
