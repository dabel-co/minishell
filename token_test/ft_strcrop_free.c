/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:35:45 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/17 20:43:43 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcrop_free(char *str, unsigned int start, size_t len)
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
	free(str);
	return (ret);
}
