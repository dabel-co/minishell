/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:52:31 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/01 15:24:30 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_exec	*tokenizator(char **orders, t_envir *env)
{
	t_exec	*ret;
	t_exec	*new;
	char	*last_bar;
	
	ret = (t_exec*)malloc(sizeof(t_exec));
	new = ret;
	while (*orders)
	{
		ft_bzero(new, sizeof(t_exec));
		//poner Víctor a cero
		/*if (syntax_err(*orders))
		{
			free_tokens(ret);
			return(NULL);
		}*/
		new->in_fd = take_all_heredoc(orders);
		//aquí va un expand
		take_all_redir(orders, new);
		//aquí hay que detenerse si ha habido un error de redirección (err_msg no es nulo), también hay que revisar que quede algo
		*orders = ft_strtrim(*orders, " "); //AQUÏ FALTA UN FREE
		if (**orders)
		{
			new->argv = smart_split(*orders, ' ');
			last_bar = ft_strrchr(new->argv[0], '/');
			if (last_bar)
			{
				new->exec_path = new->argv[0];
				if (access(new->exec_path, F_OK) < 0)
					new->err_msg = ft_strdup("el ejecutable no se ha encontrado");
				new->argv[0] = strdup(last_bar + sizeof(char));
			}
			else
				new->exec_path = search_comm(new->argv[0], env->paths, new);
		}
		orders++;
		if (*orders)
			new->next = (t_exec*)malloc(sizeof(t_exec));
		new = new->next;
	}
	return (ret);
}
/*
int	main()
{
	char	*input = "hola >hola | \"hola\"\"como | pp42 estas\"42 sin la nada";

	print_close(tokenizator(smart_split(input, '|')));
}*/
