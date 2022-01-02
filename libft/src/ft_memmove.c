/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:13:28 by dabel-co          #+#    #+#             */
/*   Updated: 2021/10/27 16:08:13 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*x;
	const char	*y;

	x = dst;
	y = src;
	if (!dst && !src)
		return (NULL);
	if (x < y)
	{
		while (len--)
			*x++ = *y++;
	}
	else
	{
		x = x + (len - 1);
		y = y + (len - 1);
		while (len--)
			*x-- = *y--;
	}
	return (dst);
}
