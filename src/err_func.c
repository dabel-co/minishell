/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:41:33 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/09 13:07:49 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*err_syntax(char problem)
{
	char	err_str[2];
	char	*ret;

	err_str[1] = '\0';
	err_str[0] = problem;
	if (problem == '\'' || problem == '\"')
		return (ft_strjoin(ERR_SYNT_Q, err_str));
	if (!problem)
		return (ft_strjoin(ERR_SYNT_T, "newline'"));
	ret = ft_strjoin(ERR_SYNT_T, err_str);
	return (ft_strjoin_free(ret, "'"));
}

char	*err_file(char *filename, char *error)
{
	char	*ret;
	
	ret = ft_strjoin("minishell: ", filename);
	ret = ft_strjoin_free(ret, ": ");
	ret = ft_strjoin_free(ret, error);
	return (ret);
}
