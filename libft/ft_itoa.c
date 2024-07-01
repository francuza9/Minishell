/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:21:20 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/06 02:38:23 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_len(long int n);
static long int	ft_isnegative(int n, int *neg);

char	*ft_itoa(int n)
{
	char		*s;
	size_t		len;
	size_t		i;
	int			neg;
	long int	num;

	neg = 0;
	num = ft_isnegative(n, &neg);
	len = ft_get_len(num);
	s = malloc(len + neg + 1);
	if (s == NULL)
		return (NULL);
	if (neg)
		s[0] = '-';
	i = 1;
	while (i <= len)
	{
		s[len + neg - i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	s[len + neg] = '\0';
	return (s);
}

static size_t	ft_get_len(long int n)
{
	size_t	len;

	len = 1;
	while (n / 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static long int	ft_isnegative(int n, int *neg)
{
	long int	num;

	if (n < 0)
	{
		num = (long int)n * -1;
		*neg = 1;
	}
	else
		num = n;
	return (num);
}
