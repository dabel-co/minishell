/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:28:17 by dabel-co          #+#    #+#             */
/*   Updated: 2021/08/30 16:10:58 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_x(t_data *d, char type)
{
	unsigned int	num;
	unsigned long	p;

	if (type == 'p')
	{
		p = va_arg(d->argv, unsigned long);
		ft_putchar('0', d, 1);
		ft_putchar('x', d, 1);
		if (p == 0)
			ft_putchar ('0', d, 1);
		ft_putnbr_base(p, "0123456789abcdef", d);
	}
	else
	{
		num = va_arg(d->argv, unsigned int);
		if (num == 0)
			ft_putchar ('0', d, 1);
		if (type == 'x')
			ft_putnbr_base(num, "0123456789abcdef", d);
		if (type == 'X')
			ft_putnbr_base(num, "0123456789ABCDEF", d);
	}
}
