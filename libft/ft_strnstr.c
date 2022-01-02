/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:07:03 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/24 19:51:56 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fullcoinc(const char *big, const char *lil, size_t len, size_t indb)
{
	size_t	indl;

	indl = 0;
	while (lil[indl] != 0)
	{
		if (big[indb] != lil[indl] || indb >= len)
			return (0);
		indb++;
		indl++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	size_t	indb;

	indb = 0;
	if (lil[0] == 0)
		return ((char *)big);
	while (indb < len && big[indb] != 0)
	{
		if (big[indb] == lil[0] && fullcoinc(big, lil, len, indb))
			return ((char *)big + indb);
		indb++;
	}
	return (NULL);
}
