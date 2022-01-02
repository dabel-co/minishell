/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:50:05 by dabel-co          #+#    #+#             */
/*   Updated: 2021/08/30 13:25:12 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_int(t_data *d)
{
	int	num;

	num = va_arg(d->argv, int);
	ft_putnbr(num, d);
}

void	ft_u(t_data *d)
{
	unsigned int	u;

	u = va_arg(d->argv, unsigned int);
	ft_putnbr(u, d);
}
