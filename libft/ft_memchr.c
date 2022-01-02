/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:27:26 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:39:08 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(void *scan, int srch, size_t len)
{
	size_t	ind;

	ind = 0;
	while (ind < len)
	{
		if (*((char *)scan + ind) == (char)srch)
			return ((void *)((char *)scan + ind));
		ind++;
	}
	return (NULL);
}
