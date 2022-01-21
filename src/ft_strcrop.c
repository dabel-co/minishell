/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:45:06 by marvin            #+#    #+#             */
/*   Updated: 2022/01/21 11:45:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcrop(char const *str, unsigned int start, size_t len)
{
	char				*ret;
	unsigned int		ind;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	ind = 0;
	while (ind < start)
	{
		ret[ind] = str[ind];
		ind++;
	}
	while (str[ind + len])
	{
		ret[ind] = str[ind + len];
		ind++;
	}
	ret[ind] = '\0';
	return (ret);
}