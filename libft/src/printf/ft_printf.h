/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:13:00 by dabel-co          #+#    #+#             */
/*   Updated: 2021/12/16 12:30:53 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

typedef struct s_data
{
	va_list	argv;
	int		count;
}				t_data;

int			ft_printf(const char *input, ...);
const char	*ft_flags(const char *str, t_data *d);
void		ft_putchar(char x, t_data *d, int n);
void		ft_int(t_data *d);
void		ft_char(t_data *d, char type);
void		ft_send(const char *c, t_data *d);
void		ft_putnbr(long nb, t_data *d);
void		ft_reset_data(t_data *d);
int			ft_numlen(int n);
void		ft_u(t_data *d);
void		ft_x(t_data *d, char type);
void		ft_putnbr_base(unsigned long nb, char *base, t_data *d);
#endif
