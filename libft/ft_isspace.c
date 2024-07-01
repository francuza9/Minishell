/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:47:41 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/01/14 16:49:32 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	int		i;
	char	spaces[6];

	spaces[0] = ' ';
	spaces[1] = '\f';
	spaces[2] = '\t';
	spaces[3] = '\v';
	spaces[4] = '\n';
	spaces[5] = '\r';
	i = 0;
	while (i < 6)
	{
		if (c == (int)spaces[i])
			return (1);
		i++;
	}
	return (0);
}
