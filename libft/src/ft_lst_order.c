/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:21:12 by dabel-co          #+#    #+#             */
/*   Updated: 2021/11/19 18:47:32 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_order(t_list *a)
{
	t_list	*aux;

	aux = a;
	while (aux->next != NULL)
	{
		if (*(int *)aux->content > *(int *)aux->next->content)
			return (-1);
		aux = aux->next;
	}
	return (0);
}
