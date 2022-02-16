/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:52:31 by vguttenb          #+#    #+#             */
/*   Updated: 2022/02/16 18:55:10 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_exec
{
	char	*exec_path;
	char	**argv;
	int		in_fd;
	int		out_fd;
	char	*err_msg;
	t_exec	*next;
}				t_exec;

int	arg_counter(char *order)
{
	int		ret;
	char	limiter;

	ret = 0;
	while (*order == ' ')
		order++;
	while (*order)
	{
		if (*order == '\\')
			order++;
		else if (*order == '\'' || *order == '\"')
		{
			ret++;
			limiter = *order;
			while (*order != limiter)
				order++;
		}
		else if (*order == ' ')
			while (*(order + sizeof(char)) && *(order + sizeof(char)) == ' ')
				order++;
		else
		{
			ret++;
			while (*order && *order != ' ')
				order++;
		}
		if (*order)
			order++;
	}
}

int	arg_counter(char *order, int counter)
{
	int	ret;

	ret = 0;
	while (*order)
	{
		while (*order && *order == ' ')
			order++;
		if (*order)
			ret++;
		while (*order && *order != ' ')
		{
			if (*order == '\\')
				order++;
			else if (*order == '\'' || *order == '\"')
			{
				limiter = *order;
				order++;
				while (*order != limiter)
					order++;
			}
			order++;
		}
	}
	return (ret);	
}
	
char	*take_arg(char **order);
{
	int		size;
	int		ind;
	char	*ret;

	size = 0;
	while (*order[size] && *order[size] != ' ')
	{
		if (*order[size] == '\\')
			size++;
		else if (*order[size] == '\'' || *order[size] == '\"')
		{
			limiter = *order[size];
			size++;
			while (*order[size] != limiter)
				size++;
		}
		size++;
	}
	ret = (char*)malloc(sizeof(char) * (size + 1));
	ret[size--] == '\0';
	while(size >= 0)
	{
		ret[size] = *order[size]
		size--;
	}
}

char	**smart_split(char *order)
{
	int		num;
	char	**ret;
	int		ind;
	char	*iter;

	num = arg_counter(order);
	if (!num)
		return (NULL);
	ret = (char**)malloc((num + 1) * sizeof(char*));
	ind = 0;
	iter = order;
	while (ind <= num)
	{
		while (*iter == ' ')
			iter++;
		ret[ind++] = take_arg(&iter);
	}
}

t_exec	*tokenizator(char **orders);
{
	t_exec	*ret;
	t_exec	*new;
	char	*last_bar;
	
	ret = (t_exec*)malloc(sizeof(t_exec));
	new = ret;
	while (*orders)
	{
		//poner todo a cero
		/*if (syntax_err(*orders))
		{
			free_tokens(ret);
			return(NULL);
		}*/
		new->rfd = take_all_heredoc(orders);
		//aquí va un expand
		take_all_redir(orders, new);
		//aquí hay que detenerse si ha habido un error de redirección (err_msg no es nulo), también hay que revisar que quede algo
		new->argv = smart_split(*orders);
		last_bar = ft_strrchr(new->argv[0], '/');
		if (last_bar)
		{
			new->exec_path = strdup(argv[0]);
			if (access(new->exec_path, F_OK) < 0)
				new->err_msg = no path;
			argv[0] = strdup(last_bar + sizeof(char));
		}
		else
		{
			if (!is_builtin(argv[0]))
				new->exec_path = search_exec(argv[0]);
		}
		orders++;
		if (*orders)
			new->next = (t_exec*)malloc(sizeof(t_exec));
		new = new->next;
	}
}
