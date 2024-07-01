/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:43:55 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/11/17 15:44:39 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			args;
	int				count;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = 0;
	count = ft_parse(format, &args);
	va_end(args);
	return (count);
}
