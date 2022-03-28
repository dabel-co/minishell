/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:35:43 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/23 17:23:11 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	limiter;
	char	*iter;
	char	*copy;
	
	iter = str;
	copy = str;
	limiter = '\0';
	while (*iter)
	{
		if (limiter && *iter == limiter)
			limiter = '\0';
		else if (!limiter && (*iter == '\'' || *iter == '\"'))
			limiter = *iter;
		else
			*copy++ = *iter;
		iter++;
	}
	*copy = '\0';
	copy = ft_strdup(str);
	free(str);
	return (copy);
}

// int main()
// {
// 	char *x = ft_strdup("\"\'\"\'\"hey hola\"\'\"\'\"");
// 	x = remove_quotes(x);
// 	printf("%s\n", x);
// 	free(x);
// 	system("leaks a.out");
// }
