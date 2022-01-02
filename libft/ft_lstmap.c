/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:40:52 by vguttenb          #+#    #+#             */
/*   Updated: 2021/05/15 14:36:11 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*nxt;

	if (!lst)
		return (NULL);
	nxt = ft_lstnew(f(lst->content));
	if (!nxt)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	newlst = nxt;
	lst = lst->next;
	while (lst)
	{
		nxt = ft_lstnew(f(lst->content));
		lst = lst->next;
		ft_lstadd_back(&newlst, nxt);
	}
	return (newlst);
}
