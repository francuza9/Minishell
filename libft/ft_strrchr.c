/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:58:36 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/11/05 18:51:39 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*check;

	check = (char *)s;
	while (*check != '\0')
		check++;
	if ((char)c == '\0')
		return (check);
	while (check != (s - 1))
	{
		if (*check == (char)c)
			return (check);
		check--;
	}
	return (NULL);
}
