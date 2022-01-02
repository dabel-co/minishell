/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:29:47 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 18:54:36 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t numb, size_t size)
{
	void	*here;

	here = malloc(numb * size);
	if (!here)
		return (NULL);
	ft_bzero(here, numb * size);
	return (here);
}
