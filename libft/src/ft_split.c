/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:38:30 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/18 14:26:33 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlines(const char *s, char c, int a, int b)
{
	if (!s || *s == '\0')
		return (0);
	while (s[a] == c && s[a] != '\0')
		a++;
	while (s[a] != '\0')
	{
		if (s[a] == c && s[a + 1] != c && s[a + 1] != '\0')
			b++;
		a++;
	}
	return (b);
}

static int	ft_getsize(const char *s, char c, int i)
{
	int	x;

	x = 0;
	while (s[x] != c && s[x] != '\0')
	{
		i++;
		x++;
	}
	return (i + 1);
}

static char	**ft_fill(const char *s, char **split, char c, int lines)
{
	int	l;
	int	f;
	int	i;

	l = 0;
	i = 0;
	while (l < lines)
	{
		f = 0;
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		split[l] = malloc(ft_getsize(&s[i], c, 0) * sizeof(char));
		while (s[i] != c && s[i] != '\0')
			split[l][f++] = s[i++];
		split[l][f] = '\0';
		l++;
	}
	split[l] = NULL;
	l = 0;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	int		lines;

	if (!s)
		return (NULL);
	lines = ft_getlines(s, c, 0, 1);
	split = (char **)malloc((lines + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_fill(s, split, c, lines));
}
