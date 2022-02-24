/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:09:53 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/24 17:04:53 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_op(char *comm, char search)
{
	char	limiter;

	limiter = '\0';
	while (*comm && (*comm != search || limiter))
	{
		if (*comm == '\\')
			comm++;
		else if (*comm == '\'' || *comm == '\"')
		{
			if (!limiter)
				limiter = *comm;
			else if (*comm == limiter)
				limiter = '\0';
		}
		comm++;
	}
	if (*comm)
		return (comm);
	return (NULL);
}
