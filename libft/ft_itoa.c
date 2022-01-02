/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:24:17 by vguttenb          #+#    #+#             */
/*   Updated: 2021/05/02 19:52:52 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numsize(int n, int *pexp)
{
	size_t	val;

	val = 0;
	while (n / pexp[0] != 0 && pexp[0] != 1000000000)
	{
		pexp[0] = pexp[0] * 10;
		val++;
	}
	if (pexp[0] == 1000000000 && n / pexp[0] != 0)
		val++;
	if (n < 0)
		val++;
	if (n == 0)
		val++;
	return (val);
}

static void	assign(char *s, int n, int exp)
{
	size_t	ind;

	ind = 0;
	if ((exp == 1000000000 || exp == -1000000000) && n / exp != 0)
		s[ind++] = n / exp + 48;
	while (exp != 1 && exp != -1)
	{
		s[ind++] = ((n % exp) / (exp / 10)) + 48;
		exp = exp / 10;
	}
	if (n == 0)
		s[ind++] = '0';
	s[ind] = 0;
}

char	*ft_itoa(int n)
{
	int		exp;
	int		*pexp;
	char	*ret;
	size_t	ind;

	exp = 1;
	pexp = &exp;
	ind = 0;
	ret = malloc(numsize(n, pexp) + 1);
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		ret[ind++] = '-';
		exp = -exp;
	}
	assign(&ret[ind], n, exp);
	return (ret);
}
