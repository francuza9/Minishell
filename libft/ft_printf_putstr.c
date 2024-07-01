/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:14:10 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/01/28 16:14:41 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putchar(unsigned char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_putstr(char *s)
{
	size_t	count;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	count = 0;
	while (*s != '\0')
	{
		write(1, s, 1);
		s++;
		count++;
	}
	return (count);
}
