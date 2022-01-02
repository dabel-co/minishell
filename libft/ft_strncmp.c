/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:25:19 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:53:16 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t	ind;

	ind = 0;
	if (len == 0)
		return (0);
	while (ind < len)
	{
		if (str1[ind] == 0)
			return ((int) -(unsigned char)str2[ind]);
		if (str2[ind] == 0)
			return ((int)(unsigned char)str1[ind]);
		if (str1[ind] != str2[ind])
			return ((int)((unsigned char)str1[ind] - (unsigned char)str2[ind]));
		ind++;
	}
	return (0);
}
