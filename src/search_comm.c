/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_comm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:45:56 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/24 17:49:39 by vguttenb         ###   ########.fr       */
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

int	is_builtin(char *str)
{
	char	**built_in;
	int		ind;

	built_in = (char *[]){"cd", "export", "unset", "echo", "env", "pwd", NULL};
	ind = 0;
	while (built_in[ind])
		if (ft_strcmp(built_in[ind++], str))
			return (ind);
	return (0);
}

char	*search_comm(char *comm, char **paths, t_exec *exec)
{
	int		i;
	char	*ret;

	i = is_builtin(comm);
	if (i > 3)
		return(ft_strdup(comm));
	if (i)
		return (NULL);
	while (paths[i] && paths[i][0]) //Y ESA SEGUNDA COMPROBACIÓN A QUÉ DEMONIOS VIENE
	{
		ret = ft_strjoin(paths[i], "/");
		ret = strjoin_free(ret, comm);
		//ft_putnbr_fd(access(ret, F_OK), 1);
		//ft_putstr_fd(" -> ", 1);
		//ft_putstr_fd(ret, 1);
		if (access(ret, F_OK) > -1)
			return (ret);
		free(ret);
		i++;
	}
	exec->err_msg = ft_strdup("el ejecutable no se ha encontrado");
	return (NULL);
}
