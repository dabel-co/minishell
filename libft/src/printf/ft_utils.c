/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 17:14:38 by dabel-co          #+#    #+#             */
/*   Updated: 2021/08/30 16:26:52 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long nb, char *base, t_data *d)
{
	if (nb)
	{
		ft_putnbr_base(nb / 16, &base[0], d);
		ft_putchar(base[nb % 16], d, 1);
	}	
}

void	ft_putnbr(long nb, t_data *d)
{
	if (nb == -2147483648)
	{
		ft_putchar('-', d, 1);
		ft_putchar('2', d, 1);
		ft_putnbr(147483648, d);
		return ;
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10, d);
		ft_putnbr(nb % 10, d);
	}
	else if (nb < 0)
	{
		ft_putchar(-3 + '0', d, 1);
		ft_putnbr(-nb, d);
	}
	else
		ft_putchar(nb + '0', d, 1);
}

void	ft_putchar(char x, t_data *d, int n)
{
	int	p;

	p = n;
	if (n < 0)
	{
		n = 0;
		p = 0;
	}
	while (n > 0)
	{
		write(1, &x, 1);
		n--;
	}
	d->count = d->count + p;
}
