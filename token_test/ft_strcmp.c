/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:50:48 by dabel-co          #+#    #+#             */
/*   Updated: 2022/01/31 11:51:21 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
