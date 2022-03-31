/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguttenb <vguttenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:41:33 by vguttenb          #+#    #+#             */
/*   Updated: 2022/03/31 18:42:17 by vguttenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*err_file(char *filename, char *error)
{
	char	*ret;

	ret = ft_strjoin("minishell: ", filename);
	ret = ft_strjoin_free(ret, ": ");
	ret = ft_strjoin_free(ret, error);
	return (ret);
}
