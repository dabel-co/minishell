/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:08:26 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/17 15:29:51 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*x;
	size_t	a;
	int		test;

	if (!s)
		return (NULL);
	test = ft_strlen(s);
	if (start > ft_strlen(s))
	{
		x = malloc(1);
		x[0] = '\0';
		return (x);
	}
	if (ft_strlen(s) < len)
		x = malloc(ft_strlen(s));
	else
		x = malloc(len + 1);
	if (!x)
		return (NULL);
	a = 0;
	while (test-- && len--)
		x[a++] = s[start++];
	x[a] = '\0';
	return (x);
}
