/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:23:44 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/11/05 17:10:05 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*ptr;

	ptr = dest;
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			*((char *)dest + i - 1) = *((char *)src + i - 1);
			i--;
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	return (ptr);
}
