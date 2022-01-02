/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:25:22 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/25 19:02:25 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	ind;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		result = malloc (1);
		result[0] = 0;
		return (result);
	}
	if ((ft_strlen(s) - start + 1) < len)
		len = ft_strlen(s) - start;
	result = malloc(len + 1);
	ind = 0;
	if (!result)
		return (NULL);
	while (ind < len && s[start])
	{
		result[ind] = s[start];
		start++;
		ind++;
	}
	result[ind] = 0;
	return (result);
}
