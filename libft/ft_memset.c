/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:45:22 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:37:07 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *memdir, int value, size_t len)
{
	size_t	ind;

	ind = 0;
	while (ind < len)
	{
		*((unsigned char *)memdir + ind) = (unsigned char)value;
		ind++;
	}
	return (memdir);
}
