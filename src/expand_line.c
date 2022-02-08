/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:46:32 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/08 15:40:25 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//probably should mode this somewhere later when we have it figured out
//gotta discuss this thingy
/* 
char	*expand(char *str, t_envir *env)
{
	int		i;
	int		p;
	char	*aux;

	i = 0;
	p = 0;
	str++;
	while (find_env(env->e_envp[i], str))
		i++;
	while (env->e_envp[i][p] != '=')
		p++;
	aux = malloc(ft_strlen(&env->e_envp[i][p]) * sizeof(char));
	ft_strlcpy(aux, &env->e_envp[i][p + 1], ft_strlen(&env->e_envp[i][p]) + 1);
	return (aux);
}

t_execord	*fill_line(char *orders, int i, int p, int r)
{
	while (orders[i] != '|'  || orders[i] != '\0')
	{
		if (orders[i] == '<' && orders[i + 1] == '<' && orders[i + 2] == ' ')
			orders = fill_eof(x);
		if (orders[i] == '"' || orders[i] ==
	}
}
//split inteligente
t_execord	*init_line(char **orders)
{
	int	i;
	int t;
	t_execord	*x;

	i = 0;
	t = 0;
	x = NULL;
	while (orders[i])
	{
		if (orders[i] == '"' || orders[i] == ''')
			t++;
		//add space changer
		i++;
	}
	if ( t % 2 != 0)
		return (NULL); //error de comillas, no estan bien cerradas
	//add malloc
	i = 0;
	while (i < 3) // add counter of the ||| thingy
	{
		x[i] = fill_line(orders, 0, 0, 0);
		//advance line
		i++;
	}
	x[i] = NULL;
	return (x);
}
*/
//inteligent split init
static int	split_size(char *str, int mode)
{
	int i;
	int	count;
	int check;

	i = 0;
	count = 1;
	check = 0;
	while (1)
	{
		if ((str[i] == '"' || str[i] == '\'') && check == 0)
			check++;
		else if ((str[i] == '"' || str[i] == '\'') && check == 1)
			check--;
		else if (str[i] == '|' && check == 0 && mode == 0)
			count++;
		else if ((str[i] == '|' || str[i] == '\0') && check == 0 && mode == 1)
			return (i);
		else if (str[i] == '\0')
			break;
		i++;
	}
	return (count);
}

static char *fill_split(char *str, int *p)
{
	int i;
	int check;
	char *aux;

	i = 0;
	check = 0;
	aux = (char *)malloc((split_size(str, 1)) + 1 * sizeof(char));
	//printf("RESERVED SIZE ->%d\n", (split_size(str, 1) + 1));
	while (1)
	{
		if ((str[i] == '"' || str[i] == '\'') && check == 0)
			check++;
		else if ((str[i] == '"' || str[i] == '\'') && check == 1)
			check--;
		else if ((str[i] == '|' || str[i] == '\0') && check == 0)
		{
			aux[i] = '\0';
			*p = i + 1;
			return (aux);
		}
		//printf("helaaaaaaaaao\n");
		aux[i] = str[i];
		i++;
	}
}
char **init_split(char *str)
{
	char **split;
	int i;
	int x;
	int p;

	i = 0;
	p = 0;
	x = split_size(str, 0);
	split = malloc((x + 1) * sizeof(char *));
	while (i < x)
	{
		printf("FULL STR -> %s\n", str);
		split[i] = fill_split(str, &p);
	//	printf("->%s\nint : %d\n", split[i], p);
		while (p >= 0)
		{
			str++;
			p--;
		}
		i++;
	}
	//printf("NUMERO X %d NUMERO I %d\n", x, i);
	split[i] = NULL;
	return (split);
}

//split end
