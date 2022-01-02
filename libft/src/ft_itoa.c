/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:21:57 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/21 10:41:32 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n >= 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_min(int n)
{
	char	*result;
	int		i;

	i = 10;
	if (n == 0)
	{
		result = malloc(2);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	result = malloc(12);
	result[11] = '\0';
	result[0] = '-';
	result[1] = '2';
	n = 147483648;
	while (i > 1)
	{
		result[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;

	if (n == -2147483648 || n == 0)
		return (ft_min(n));
	size = ft_getsize(n);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		n = n * -1;
	}
	result[size] = '\0';
	while (n)
	{
		result[--size] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
