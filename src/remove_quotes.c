/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:35:43 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 18:38:28 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	limiter;
	char	*iter;
	char	*copy;

	iter = str;
	copy = str;
	limiter = '\0';
	while (*iter)
	{
		if (limiter && *iter == limiter)
			limiter = '\0';
		else if (!limiter && (*iter == '\'' || *iter == '\"'))
			limiter = *iter;
		else
			*copy++ = *iter;
		iter++;
	}
	*copy = '\0';
	copy = ft_strdup(str);
	free(str);
	return (copy);
}
