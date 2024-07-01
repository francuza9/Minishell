/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:44:14 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/11/05 20:08:19 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*end;
	const char	*current;

	end = dst + size;
	if (end < dst)
		end = dst + ft_strlen(src) + 1;
	current = src;
	while (*current != '\0' && dst < end)
		*dst++ = *current++;
	if (dst < end)
		*dst = '\0';
	else if (size > 0)
		dst[-1] = '\0';
	while (*current != '\0')
		current++;
	return (current - src);
}
