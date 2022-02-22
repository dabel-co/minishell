/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <dabel-co@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:59:02 by dabel-co          #+#    #+#             */
/*   Updated: 2022/02/22 17:47:09 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *remove_quotes(char *str)
{
	char	limiter;
	int		counter;
	int		ind;
	char	*ret;

	counter = 0;
	ind = 0;
	limiter = '\0';
	while(str[ind + counter])
	{
		if (limiter && str[ind + counter] == limiter)
		{
			limiter = '\0';
			counter++;
		}
		else if (!limiter && (str[ind + counter] == '\'' || str[ind + counter] == '\"'))
		{
			limiter = str[ind + counter];
			counter++;
		}
		else
		{
			str[ind] = str[ind + counter];
			ind++;
		}
	}
	str[ind] = '\0';
	ret = ft_strdup(str);
	free(str);
	return (ret);
}
int main()
{
	char *x = ft_strdup("\"\'\"\'\"\'hey hola\"\'\"\'\"");
	x = remove_quotes(x);
	printf("%s\n", x);
	free(x);
	system("leaks a.out");
}
