/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:30:24 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:45:53 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	inds;
	size_t	indd;
	size_t	finalsize;

	inds = 0;
	indd = ft_strlen(dst);
	if (len <= indd)
		return (ft_strlen(src) + len);
	else
		finalsize = ft_strlen(src) + ft_strlen(dst);
	while (indd < len - 1 && src[inds] != 0)
	{
		dst[indd] = src[inds];
		inds++;
		indd++;
	}
	dst[indd] = 0;
	return (finalsize);
}
