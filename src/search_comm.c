/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_comm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:45:56 by vguttenb          #+#    #+#             */
/*   Updated: 2022/01/26 15:32:22 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strjoin_free(char *keeper, char *buffer)
{
	int		size;
	int		ind1;
	int		ind2;
	char	*result;

	ind1 = -1;
	ind2 = 0;
	size = ft_strlen(keeper) + ft_strlen(buffer);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (keeper)
		while (keeper[++ind1])
			result[ind1] = keeper[ind1];
	else
		ind1++;
	if (buffer)
		while (buffer[ind2])
			result[ind1++] = buffer[ind2++];
	result[ind1] = '\0';
	free (keeper);
	return (result);
}

char	*search_comm(char *comm, char **paths)
{
	int		i;
	char	*ret;

	i = 0;
	while (paths[i] && paths[i][0])
	{
		ret = ft_strjoin(paths[i], "/");
		ret = strjoin_free(ret, comm);
		if (access(ret, F_OK) > -1)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}
