/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:13:54 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/01/01 22:14:02 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_display_base(long int num, char *base, size_t *count);
static void	ft_display_ptr(unsigned long int ptr, size_t *count);

size_t	ft_putnbr_base(long int n, char *base)
{
	size_t		count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	ft_display_base(n, base, &count);
	return (count);
}

size_t	ft_putptr(unsigned long int ptr)
{
	size_t	count;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = 2;
	ft_display_ptr(ptr, &count);
	return (count);
}

static void	ft_display_ptr(unsigned long int ptr, size_t *count)
{
	char			disp;
	char			*base;
	unsigned long	base_int;

	base = ft_strdup("0123456789abcdef");
	base_int = ft_strlen(base);
	if (ptr < base_int)
	{
		disp = base[ptr];
		write(1, &disp, 1);
		(*count)++;
	}
	else
	{
		ft_display_ptr(ptr / base_int, count);
		ft_display_ptr(ptr % base_int, count);
	}
	free(base);
}

static void	ft_display_base(long int num, char *base, size_t *count)
{
	char		disp;
	long int	base_int;

	base_int = (long int) ft_strlen(base);
	if (num < base_int)
	{
		disp = base[num];
		write(1, &disp, 1);
		(*count)++;
	}
	else
	{
		ft_display_base(num / base_int, base, count);
		ft_display_base(num % base_int, base, count);
	}
}
