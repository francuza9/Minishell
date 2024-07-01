/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:04:18 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/11/05 18:00:48 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	m;

	if (*little == '\0')
		return ((char *)big);
	m = ft_strlen(little);
	while (len && *big != '\0')
	{
		if (len < m)
			break ;
		if (!ft_strncmp(big, little, m))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
