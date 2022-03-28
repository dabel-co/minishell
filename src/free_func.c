/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:13:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/28 17:29:19 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	char	**to_free;

	to_free = array;
	while (*array)
		free(*array++);
	free(to_free);
}

void	free_node(t_exec *node)
{
	if (node->in_fd > 0)
		close(node->in_fd);
	if (node->out_fd && node->out_fd != STDOUT_FILENO)
		close(node->out_fd);
	if (node->exec_path)
		free(node->exec_path);
	if (node->argv)
		free_array(node->argv);
	if (node->err_msg)
		free(node->err_msg);
	free(node);
}

// void	free_node(t_exec *node)
// {
// 	ft_putstr_fd("I'm ", STDERR_FILENO);
// 	ft_putstr_fd(node->argv[0], STDERR_FILENO);
// 	ft_putendl_fd(" and I'm going to free:", STDERR_FILENO);
// 	if (node->in_fd > 0)
// 	{
// 		ft_putstr_fd("Input fd:", STDERR_FILENO);
// 		ft_putnbr_fd(node->in_fd, STDERR_FILENO);
// 		ft_putchar_fd('\n', STDERR_FILENO);
// 		close(node->in_fd);
// 	}
// 	if (node->out_fd)
// 	{
// 		ft_putstr_fd("Output fd:", STDERR_FILENO);
// 		ft_putnbr_fd(node->out_fd, STDERR_FILENO);
// 		ft_putchar_fd('\n', STDERR_FILENO);
// 		close(node->out_fd);
// 	}
// 	if (node->exec_path)
// 		free(node->exec_path);
// 	if (node->argv)
// 		free_array(node->argv);
// 	if (node->err_msg)
// 		free(node->err_msg);
// 	free(node);
// }

void	free_list(t_exec *list)
{
	t_exec	*next;

	while (list)
	{
		next = list->next;
		free_node(list);
		list = next;
	}
}
