/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:24:48 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:38:10 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	ind;

	ind = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (ind < len)
	{
		*((char *)dest + ind) = *((char *)src + ind);
		ind++;
	}
	return (dest);
}
