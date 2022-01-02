/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:55:27 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/09 14:44:52 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*x;
	const char		*y;
	size_t			i;

	x = dst;
	y = src;
	i = 0;
	while (i < n)
	{
		x[i] = y[i];
		if (x[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
