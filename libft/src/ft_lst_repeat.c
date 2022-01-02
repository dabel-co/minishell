/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_repeat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:33:37 by dabel-co          #+#    #+#             */
/*   Updated: 2021/12/02 13:04:22 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_repeat(t_list *a)
{
	t_list	*aux;
	t_list	*last;

	aux = a;
	last = ft_lstlast(a);
	while (aux->next != NULL)
	{
		if (*(int *)aux->content == *(int *)last->content)
			return (-1);
		aux = aux->next;
	}
	return (0);
}
