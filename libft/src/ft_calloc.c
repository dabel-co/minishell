/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:57:25 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/13 18:16:20 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*x;

	if (count <= 0 || size <= 0)
		x = malloc(1);
	else
		x = malloc(count * size);
	if (!x)
		return (NULL);
	return (ft_memset(x, 0, count * size));
}
