/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:56:28 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/06 02:30:45 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (ft_compare(*start, set))
		start++;
	while (ft_compare(*(end - 1), set) && end > start)
		end--;
	if (start >= end)
	{
		ptr = malloc(1);
		*ptr = '\0';
		return (ptr);
	}
	ptr = malloc(end - start + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, start, end - start + 1);
	return (ptr);
}
