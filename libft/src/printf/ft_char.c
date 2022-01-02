/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 10:41:16 by dabel-co          #+#    #+#             */
/*   Updated: 2021/08/30 16:25:48 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_char(t_data *d, char type)
{
	char	*str;
	char	c;
	int		i;

	i = 0;
	if (type == 'c')
	{
		c = va_arg(d->argv, int);
		ft_putchar(c, d, 1);
	}
	else
	{
		str = va_arg(d->argv, char *);
		if (!str)
		{
			str = "(null)";
		}
		while (str[i] != '\0' && str)
		{
			ft_putchar(str[i], d, 1);
			i++;
		}
	}		
}
