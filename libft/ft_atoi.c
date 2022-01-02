/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:40:40 by vguttenb          #+#    #+#             */
/*   Updated: 2021/04/25 16:36:14 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	ind;
	size_t	start;
	long	value;

	ind = 0;
	value = 0;
	while ((str[ind] > 8 && str[ind] < 14) || str[ind] == 32)
		ind++;
	if (str[ind] == 43 || str[ind] == 45)
		ind++;
	start = ind;
	while (str[ind] && ind < start + 10)
	{
		if (!ft_isdigit(str[ind]))
			break ;
		value = value * 10 + (str[ind] - 48);
		ind++;
	}
	if ((start > 0 && str[start - 1] == '-') && value > 2147483648)
		return (0);
	if (start > 0 && str[start - 1] == '-')
		return (-value);
	else if (value > 2147483647)
		return (-1);
	return (value);
}
