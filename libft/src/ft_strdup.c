/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:57:32 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/12 17:10:20 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*x;

	i = 0;
	x = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!x)
		return (NULL);
	while (s1[i] != '\0')
	{
		x[i] = s1[i];
		i++;
	}
	x[i] = '\0';
	return (&x[0]);
}
