/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:46:14 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:38:43 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memccpy(void *dest, const void *src, int srch, size_t len)
{
	size_t	ind;

	ind = 0;
	while (ind < len && *((const char *)src + ind) != (char)srch)
	{
		*((char *)dest + ind) = *((const char *)src + ind);
		ind++;
	}
	if (ind == len)
		return (0);
	else
	{
		*((char *)dest + ind) = *((const char *)src + ind);
		dest = ((char *)dest + (ind + 1));
		return (dest);
	}
}
