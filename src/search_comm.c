/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_comm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:45:56 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 17:11:26 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *str)
{
	char	**built_in;

	built_in = (char *[]){"cd", "export", "unset", \
	"echo", "env", "pwd", "exit", NULL};
	while (*built_in)
		if (ft_strcmp(*built_in++, str))
			return (1);
	return (0);
}

char	*search_comm(char *comm, char **paths, t_exec *exec, t_envir *env)
{
	int		i;
	char	*ret;

	i = is_builtin(comm);
	if (i)
		return (NULL);
	if (paths)
	{
		while (paths[i] && paths[i][0])
		{
			ret = ft_strjoin(paths[i], "/");
			ret = ft_strjoin_free(ret, comm);
			if (access(ret, F_OK) == 0)
				return (ret);
			free(ret);
			i++;
		}
	}
	exec->err_msg = err_file(comm, "command not found");
	env->zyzz = 127;
	return (NULL);
}
