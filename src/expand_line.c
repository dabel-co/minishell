/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/10 14:59:40 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char **expand_line(char *str, t_envir *env)
{
	int i;
	char *result;

	result = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		result[i];
	}
}
