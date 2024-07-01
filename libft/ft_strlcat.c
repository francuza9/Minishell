/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:26:43 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/06 02:30:12 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*end;
	char		*current_dst;
	const char	*current_src;

	if (dst == NULL && size == 0)
		return (0);
	end = dst + size;
	if (end < dst)
		end = dst + ft_strlen(src) + ft_strlen(dst) + 1;
	current_dst = dst;
	current_src = src;
	while (*current_dst != '\0' && current_dst < end)
		current_dst++;
	while (*current_src != '\0' && current_dst < end)
		*current_dst++ = *current_src++;
	if (current_dst < end)
		*current_dst = '\0';
	else if (size > 0 && current_src != src)
		current_dst[-1] = '\0';
	while (*current_src != '\0')
	{
		current_dst++;
		current_src++;
	}
	return (current_dst - dst);
}
