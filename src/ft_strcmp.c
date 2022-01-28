/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 22:13:03 by marvin            #+#    #+#             */
/*   Updated: 2022/01/28 22:13:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	while (*str1 && *str2)
		if (*str1++ != *str2++)
			return (0);
	if (*str1 || *str2)
		return (0);
	return (1);
}
