/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:52:31 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 18:38:14 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_exec_path(t_exec *node, t_envir *env)
{
	struct stat	info;

	if (access(node->exec_path, X_OK) < 0)
	{
		node->err_msg = err_file(node->exec_path, strerror(errno));
		env->zyzz = 126;
	}
	else
	{
		stat(node->exec_path, &info);
		if (S_ISDIR(info.st_mode) || ft_strcmp(node->exec_path, "/"))
		{
			node->err_msg = err_file(node->exec_path, "is a directory");
			env->zyzz = 126;
		}
	}
}

static void	get_args(char **order, t_envir *env, t_exec *node)
{
	char	*last_bar;
	char	**iter;

	if (**order)
	{
		node->argv = smart_split(*order, ' ');
		iter = node->argv;
		while (*iter)
		{
			*iter = remove_quotes(expand_line(*iter, env, '\0'));
			iter++;
		}
		last_bar = ft_strrchr(node->argv[0], '/');
		if (last_bar)
		{
			node->exec_path = node->argv[0];
			check_exec_path(node, env);
			node->argv[0] = strdup(last_bar + 1);
		}
		else
			node->exec_path = search_comm(node->argv[0], env->paths, node, env);
	}
}

static void	update_underscore(char *line, t_envir *env)
{
	int		ind;
	char	*new_val;
	char	limiter;

	ind = ft_strlen(line);
	ind--;
	limiter = '\0';
	while (ind > 0 && line[ind] != ' ')
	{
		if (line[ind] == '\'' || line[ind] == '\"')
		{
			limiter = line[ind--];
			while (line[ind] != limiter)
				ind--;
			limiter = '\0';
		}
		ind--;
	}
	if (line[ind] == ' ')
		ind++;
	new_val = remove_quotes(expand_line(ft_strdup(&line[ind]), env, '\0'));
	home_export(ft_strjoin("_=", new_val), env, 1);
	free(new_val);
}

static t_exec	*create_node(char **order, t_envir *env)
{
	t_exec	*ret;

	if (!*order)
		return (NULL);
	ret = (t_exec *)malloc(sizeof(t_exec));
	ft_bzero(ret, sizeof(t_exec));
	ret->in_fd = take_all_heredoc(order, env);
	if (g_err > 0)
		return (ret);
	if (order[0][0] && !*(order + 1))
		update_underscore(*order, env);
	take_all_redir(order, ret, env);
	if (!ret->err_msg)
		get_args(order, env, ret);
	return (ret);
}

t_exec	*tokenizator(char **orders, t_envir *env)
{
	t_exec	*ret;
	t_exec	*new;
	char	**to_free;

	if (!orders)
		return (NULL);
	to_free = orders;
	ret = create_node(orders, env);
	new = ret;
	while (*orders)
	{
		if (g_err == 1)
		{
			free_list(ret);
			ret = NULL;
			env->zyzz = 1;
			break ;
		}
		new->next = create_node(++orders, env);
		new = new->next;
	}
	free_array(to_free);
	return (ret);
}
