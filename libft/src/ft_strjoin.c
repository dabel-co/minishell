/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:24:31 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/17 16:48:23 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*x;
	int		i;
	int		a;

	if (!s1 || !s2)
		return (NULL);
	x = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!x)
		return (NULL);
	i = 0;
	a = 0;
	while (s1[i] != '\0')
		x[a++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
	{
		x[a++] = s2[i++];
	}
	x[a] = '\0';
	return (x);
}
