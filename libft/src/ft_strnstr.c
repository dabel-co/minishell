/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 20:13:27 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/17 12:10:18 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	int	i;
	int	j;
	int	l;

	l = ft_strlen(to_find);
	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && (size_t)i < len)
	{
		j = 0;
		while (j <= l)
		{
			if (str[i + j] == to_find[j] && l == j + 1
				&& (size_t)i + j < len)
				return ((char *)&str[i]);
			if (str[i + j] == to_find[j])
				j++;
			else
				break ;
		}
		i++;
	}
	return (0);
}
