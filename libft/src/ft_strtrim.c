/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:13:57 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/17 16:18:35 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		x;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	x = ft_strlen(s1);
	while (x && ft_strchr(set, s1[x]))
		x--;
	if (!x)
		return (ft_substr(s1, 200, x + 1));
	return (ft_substr(s1, 0, x + 1));
}
