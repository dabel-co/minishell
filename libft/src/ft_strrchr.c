/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:51:38 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/12 17:13:14 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;
	size_t	x;

	x = ft_strlen(s);
	s1 = (char *)s + x;
	if (*s1-- == (char)c)
		return (s1 + 1);
	while (x--)
	{
		if (*s1-- == (char)c)
			return (s1 + 1);
	}
	if ((char)c == '\0')
		return (s1);
	return (NULL);
}
