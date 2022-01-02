/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:12:53 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:47:42 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strchr(const char *str, int srch)
{
	size_t	ind;

	ind = 0;
	if (!str)
		return (NULL);
	while (str[ind] != 0)
	{
		if (str[ind] == (char)srch)
			return ((char *)(str + ind));
		ind++;
	}
	if (str[ind] == 0)
	{
		if (str[ind] == (char)srch)
			return ((char *)(str + ind));
	}
	return (NULL);
}
