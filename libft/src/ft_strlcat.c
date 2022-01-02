/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 14:40:48 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/17 09:59:03 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	x;

	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	i = 0;
	d = ft_strlen(dst);
	x = d;
	while (d + 1 < dstsize && src[i] != '\0')
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	dst[d] = '\0';
	return (ft_strlen(src) + x);
}
