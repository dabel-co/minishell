/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:13:52 by vguttenb          #+#    #+#             */
/*   Updated: 2022/04/07 11:56:27 by dabel-co         ###   ########.fr       */
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
