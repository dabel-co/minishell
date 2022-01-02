/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:05:13 by vguttenb          #+#    #+#             */
/*   Updated: 2021/05/01 13:00:52 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	coinc(char const cmp, char const *set)
{
	size_t	indset;

	indset = 0;
	while (set[indset])
	{
		if (cmp == set[indset])
			return (1);
		indset++;
	}
	return (0);
}

static size_t	strtpnt(char const *s1, char const *set)
{
	size_t	str;

	str = 0;
	while (coinc(s1[str], set))
		str++;
	return (str);
}

static size_t	finalpnt(char const *s1, char const *set)
{
	int	fnl;

	fnl = ft_strlen(s1) - 1;
	while (coinc(s1[fnl], set))
	{
		fnl--;
		if (fnl < 0)
			return (0);
	}
	return (fnl);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	ind2;
	size_t	scut;
	size_t	fcut;

	ind2 = 0;
	if (!s1 || !set)
		return (NULL);
	scut = strtpnt(s1, set);
	if (scut != ft_strlen(s1))
	{
		fcut = finalpnt(s1, set);
		result = malloc(fcut - scut + 2);
		if (!result)
			return (NULL);
		while (scut <= fcut)
			result[ind2++] = s1[scut++];
	}
	else
		result = malloc(1);
	result[ind2] = 0;
	return (result);
}
