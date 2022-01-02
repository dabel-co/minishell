/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:52:01 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:46:33 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	ind;

	ind = 0;
	if (!dst || !src)
		return (0);
	if (len == 0)
		return (ft_strlen(src));
	while (ind < len - 1 && src[ind] != 0)
	{
		dst[ind] = src[ind];
		ind++;
	}
	dst[ind] = 0;
	return (ft_strlen(src));
}
