/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:40:32 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/25 17:20:42 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *dir1, const void *dir2, size_t len)
{
	size_t			ind;
	unsigned char	*cdir1;
	unsigned char	*cdir2;

	ind = 0;
	cdir1 = (unsigned char *)dir1;
	cdir2 = (unsigned char *)dir2;
	if (len == 0)
		return (0);
	while (ind < len)
	{
		if (cdir1[ind] != cdir2[ind])
			return ((int)(cdir1[ind] - cdir2[ind]));
		ind++;
	}
	return (0);
}
