/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ord_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:53:52 by marvin            #+#    #+#             */
/*   Updated: 2022/01/26 15:29:26 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ord_count(char const *comm_line)
{
	size_t	ordnum;
	size_t	ind;

	ordnum = 0;
	ind = 0;
	while (comm_line[ind])
	{
		while (ft_strchr("|<>", comm_line[ind]))
		{
			ind++;
			if (!comm_line[ind])
				return (ordnum);
		}
		ordnum++;
		while (comm_line[ind] && !ft_strchr("|<>", comm_line[ind]))
			ind++;
	}
	return (ordnum);
}

static char	*ord_cpy(char const *ord)
{
	size_t	len;
	size_t	indc;
	char	*cpy;

	len = 0;
	while (ord[len] && ft_strchr("|<>", ord[len]))
		len++;
	while (ord[len] && !ft_strchr("|<>", ord[len]))
		len++;
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	indc = 0;
	while (indc < len)
	{
		cpy[indc] = ord[indc];
		indc++;
	}
	cpy[indc] = 0;
	return (cpy);
}

char	**ord_split(char *comm_line)
{
	char	**ret;
	size_t	ord_num;
	size_t	n;
	size_t	ind;

	ord_num = ord_count(comm_line);
	ret = (char **)malloc((ord_num + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	n = 0;
	ind = 0;
	while (n < ord_num)
	{
		ret[n] = ord_cpy(&comm_line[ind]);
		while (ft_strchr("|<>", comm_line[ind]))
			ind++;
		while (!ft_strchr("|<>", comm_line[ind]))
			ind++;
		n++;
	}
	ret[n] = NULL;
	return (ret);
}
