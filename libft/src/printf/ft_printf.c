/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:11:44 by dabel-co          #+#    #+#             */
/*   Updated: 2021/08/30 10:36:28 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *input, ...)
{
	t_data	d;

	va_start(d.argv, input);
	d.count = 0;
	while (*input != '\0')
	{
		if (*input == '%')
		{
			input++;
			ft_send(input, &d);
		}
		else
			ft_putchar(*input, &d, 1);
		input++;
	}
	va_end(d.argv);
	return (d.count);
}
