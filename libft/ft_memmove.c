/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:01:01 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/16 19:23:21 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	ind;

	if (dest == 0 && src == 0)
		return (NULL);
	if (dest < src)
	{
		ind = 0;
		while (ind < len)
		{
			*((char *)dest + ind) = *((char *)src + ind);
			ind++;
		}
	}
	if (dest > src)
	{
		ind = len;
		while (ind > 0)
		{
			ind--;
			*((char *)dest + ind) = *((char *)src + ind);
		}
	}
	return (dest);
}
