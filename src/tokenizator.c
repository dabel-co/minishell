/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:52:31 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/07 11:58:45 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_args(char **order, t_envir *env, t_exec *node)
{
	char	*last_bar;
	
	last_bar = *order;
	*order = ft_strtrim(*order, " ");
	free(last_bar);
	if (**order)
	{
		node->argv = smart_split(*order, ' ');
		last_bar = ft_strrchr(node->argv[0], '/');
		if (last_bar)
		{
			node->exec_path = node->argv[0];
			if (access(node->exec_path, F_OK) < 0)
				node->err_msg = ft_strdup("el ejecutable no se ha encontrado");
			node->argv[0] = strdup(last_bar + sizeof(char));
		}
		else
			node->exec_path = search_comm(node->argv[0], env->paths, node);
	}
}

t_exec	*create_node(char **order, t_envir *env)
{
	t_exec	*ret;

	if (!*order)
		return (NULL);
	ret = (t_exec*)malloc(sizeof(t_exec));
	ft_bzero(ret, sizeof(t_exec));
	ret->in_fd = take_all_heredoc(order);
	if (g_err > 0)
		return (ret);
	*order = expand_line(*order, env, 0, 0);
	take_all_redir(order, ret);
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
			// ft_putstr_fd("saliendome porque ha habido error:", 1);
			// ft_putnbr_fd(g_err, 1);
			// ft_putchar_fd('\n', 1);
			free_list(ret);
			ret = NULL;
			break ;
		}
		new->next = create_node(++orders, env);
		new = new->next;
	}
	free_array(to_free);
	return (ret);
}

// t_exec	*tokenizator(char **orders, t_envir *env)
// {
// 	t_exec	*ret;
// 	t_exec	*new;
	
// 	ret = (t_exec*)malloc(sizeof(t_exec));
// 	new = ret;
// 	while (*orders)
// 	{
// 		ft_bzero(new, sizeof(t_exec));
// 		new->in_fd = take_all_heredoc(orders);
// 		if (new->in_fd < 0)
// 		{
// 			//free_all_tokens(ret)
// 			return (NULL)
// 		}
// 		//aquí va un expand
// 		take_all_redir(orders, new);
// 		if (!new->err_msg)
// 			get_args(orders, env, new);
// 		orders++;
// 		if (*orders)
// 			new->next = (t_exec*)malloc(sizeof(t_exec));
// 		new = new->next;
// 	}
// 	return (ret);
// }
/*
int	main()
{
	char	*input = "hola >hola | \"hola\"\"como | pp42 estas\"42 sin la nada";

	print_close(tokenizator(smart_split(input, '|')));
}*/
