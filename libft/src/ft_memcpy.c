/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:55:27 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/09 11:38:00 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*x;
	const char	*y;

	x = dst;
	y = src;
	if (!src && !dst)
		return (0);
	while (n--)
		*x++ = *y++;
	return (dst);
}
