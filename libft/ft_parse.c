/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:36:51 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/01/28 16:00:51 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	check_conversion(char conversion);
static int	ft_print_next_arg(char conversion, va_list *args);

int	ft_parse(const char *format, va_list *args)
{
	int	count;

	count = 0;
	while (*format != '\0')
	{
		if (*format == '%' && check_conversion(*(format + 1)))
		{
			format++;
			count += ft_print_next_arg(*format, args);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	return (count);
}

static int	ft_print_next_arg(char conversion, va_list *args)
{
	int	count;

	count = 0;
	if (conversion == 'c')
		count += ft_putchar(va_arg(*args, int));
	else if (conversion == 's')
		count += ft_putstr(va_arg(*args, char *));
	else if (conversion == 'p')
		count += ft_putptr(va_arg(*args, unsigned long int));
	else if (conversion == 'd' || conversion == 'i')
		count += ft_putnbr_base(va_arg(*args, int), "0123456789");
	else if (conversion == 'u')
		count += ft_putnbr_base(va_arg(*args, t_ui), "0123456789");
	else if (conversion == 'x')
		count += ft_putnbr_base(va_arg(*args, t_ui), "0123456789abcdef");
	else if (conversion == 'X')
		count += ft_putnbr_base(va_arg(*args, t_ui), "0123456789ABCDEF");
	else if (conversion == '%')
		count += ft_putchar('%');
	return (count);
}

static int	check_conversion(char conversion)
{
	char	*convs;
	size_t	i;

	convs = ft_strdup("cspdiuxX%");
	i = 0;
	while (convs[i] != '\0')
	{
		if (convs[i] == conversion)
		{
			free(convs);
			return (1);
		}
		i++;
	}
	free(convs);
	return (0);
}
