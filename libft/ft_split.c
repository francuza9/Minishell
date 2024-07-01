/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:13:23 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/02/03 21:56:08 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**allocate_word(char **arr, char *s, int len);
static char	**free_arrays(char **arr, char *word);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*i;

	arr = malloc(sizeof(char *));
	if (s == NULL || arr == NULL)
		return (NULL);
	arr[0] = NULL;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		i = (char *)s;
		while (*s != c && *s != '\0')
			s++;
		arr = allocate_word(arr, i, (int)(s - i));
		if (arr == NULL)
			return (NULL);
	}
	return (arr);
}

static char	**free_arrays(char **arr, char *word)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (word != NULL)
		free(word);
	free(arr);
	return (NULL);
}

static char	**allocate_word(char **arr, char *s, int len)
{
	int		i;
	char	*word;
	char	**new;

	word = malloc(len + 1);
	if (word == NULL)
		return (free_arrays(arr, NULL));
	ft_strlcpy(word, s, len + 1);
	i = 0;
	while (arr[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (new == NULL)
		return (free_arrays(arr, word));
	i = 0;
	while (arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = word;
	new[i + 1] = NULL;
	free(arr);
	return (new);
}
