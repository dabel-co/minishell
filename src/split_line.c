/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:46:26 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/23 10:51:41 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_size(char *str, int mode, int singles, int doubles)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (1)
	{
		if (str[i] == '"' && doubles == 0)
			doubles++;
		else if (str[i] == '"' && doubles == 1)
			doubles--;
		else if (str[i] == '\'' && singles == 0)
			singles++;
		else if (str[i] == '\'' && singles == 1)
			singles--;
		else if (str[i] == '|' && singles == 0 && doubles == 0 && mode == 0)
			count++;
		else if ((str[i] == '|' || str[i] == '\0')
			&& singles == 0 && doubles == 0 && mode == 1)
			return (i);
		else if (str[i] == '\0')
			break ;
		i++;
	}
	return (count);
}

static char	*fill_split(char *str, int *p)
{
	int		i;
	int		check;
	char	*aux;
	int		size;

	i = 0;
	check = 0;
	aux = (char *)malloc((split_size(str, 1, 0, 0)) + 1 * sizeof(char));
	size = split_size(str, 1, 0, 0);
	while (i < size)
	{
		aux[i] = str[i];
		i++;
	}
	aux[i] = '\0';
	*p = i + 1;
	return (aux);
}
char	**init_split(char *str)
{
	char **split;
	int i;
	int x;
	int p;

	i = 0;
	p = 0;
	//add even comillas checker
	x = split_size(str, 0, 0, 0);
	split = malloc((x + 1) * sizeof(char *));
	while (i < x)
	{
		split[i] = fill_split(str, &p);
		while (p >= 0)
		{
			str++;
			p--;
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}

