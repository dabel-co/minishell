/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:39:51 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 18:53:48 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	size_t	size;

	size = ft_strlen(str) + 1;
	cpy = malloc(size);
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, str, size);
	return (cpy);
}
