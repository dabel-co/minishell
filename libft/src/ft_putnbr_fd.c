/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:07:53 by dabel-co          #+#    #+#             */
/*   Updated: 2021/04/22 10:31:55 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put(char c, int fd)
{
	c = c + 48;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_put(-3, fd);
		ft_put(2, fd);
		ft_putnbr_fd(147483648, fd);
		return ;
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (n < 0)
	{
		ft_put(-3, fd);
		ft_putnbr_fd(-n, fd);
	}
	else
		ft_put(n, fd);
}
