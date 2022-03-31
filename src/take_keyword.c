/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_keyword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:13:47 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 17:07:22 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_keyword(char *str, int *end)
{
	int		ind;
	int		start;
	char	limiter;

	ind = 0;
	while (str[ind] == str[0] || str[ind] == ' ')
		ind++;
	start = ind;
	while (str[ind] && !ft_strchr("| <>", str[ind]))
	{
		if (str[ind] == '\'' || str[ind] == '\"')
		{
			limiter = str[ind];
			ind++;
			while (str[ind] != limiter)
				ind++;
		}
		ind++;
	}
	*end = ind;
	return (ft_substr(str, start, (ind - start)));
}
