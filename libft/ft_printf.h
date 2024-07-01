/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:41:16 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/01/01 22:20:47 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef unsigned int	t_ui;

int		ft_printf(const char *format, ...);
int		ft_parse(const char *format, va_list *args);
size_t	ft_putstr(char *s);
size_t	ft_putnbr_base(long int n, char *base);
size_t	ft_putchar(unsigned char c);
size_t	ft_putptr(unsigned long int ptr);

#endif
