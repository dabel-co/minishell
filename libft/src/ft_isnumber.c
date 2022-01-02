/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:33:41 by dabel-co          #+#    #+#             */
/*   Updated: 2021/11/02 19:54:39 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(int c)
{
	if (c == '-' || c == '+')
		return (1);
	if (47 < c && c < 58)
		return (1);
	return (0);
}
