/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 14:23:14 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:48:40 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int srch)
{
	size_t	ind;

	ind = ft_strlen(str);
	while (ind > 0)
	{
		if (str[ind] == (char)srch)
			return ((char *)(str + ind));
		ind--;
	}
	if (str[ind] == (char)srch)
		return ((char *)(str + ind));
	return (NULL);
}
