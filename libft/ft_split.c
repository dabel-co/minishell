/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:18:21 by vguttenb          #+#    #+#             */
/*   Updated: 2021/05/02 17:17:01 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(char const *s, char c)
{
	size_t	val;
	size_t	indw;

	val = 0;
	indw = 0;
	while (s[indw])
	{
		while (s[indw] == c)
		{
			indw++;
			if (!s[indw])
				return (val);
		}
		val++;
		while (s[indw] != c && s[indw])
			indw++;
	}
	return (val);
}

static char	*scpy(char const *s, char c, size_t ind)
{
	size_t	len;
	size_t	indc;
	char	*cpy;

	len = ind;
	indc = 0;
	while (s[len] != c && s[len] != 0)
		len++;
	cpy = malloc(len - ind + 1);
	while (ind < len)
	{
		cpy[indc] = s[ind];
		ind++;
		indc++;
	}
	cpy[indc] = 0;
	return (cpy);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	n;
	size_t	ind;

	if (!s)
		return (NULL);
	ret = (char **)malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	n = 0;
	ind = 0;
	while (s[ind])
	{
		if (s[ind] != c)
		{
			ret[n] = scpy(s, c, ind);
			n++;
			while (s[ind] != c && s[ind])
				ind++;
		}
		else
			ind++;
	}
	ret[n] = NULL;
	return (ret);
}
