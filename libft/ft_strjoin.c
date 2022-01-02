/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:31:08 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/25 18:43:30 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	ind;
	size_t	ind2;

	ind = 0;
	ind2 = 0;
	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	while (s1[ind])
	{
		result[ind] = s1[ind];
		ind++;
	}
	while (s2[ind2])
	{
		result[ind] = s2[ind2];
		ind ++;
		ind2++;
	}
	result[ind] = 0;
	return (result);
}
