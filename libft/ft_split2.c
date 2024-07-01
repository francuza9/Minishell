/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:54:22 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/02/14 21:49:48 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*parse_s(char *s);
void		enumerate_map(char *s, char *map);
static char	*mod_s(char *s, char *map, int include_quotes);
int			is_last_quote(char *s, int i);

char	**ft_split2(char const *s, int include_quotes)
{
	char	**arr;
	char	*new;
	char	*map;

	if (s == NULL)
		return (NULL);
	map = parse_s((char *)s);
	if (map == NULL)
		return (NULL);
	new = mod_s((char *)s, map, include_quotes);
	if (new == NULL)
		return (NULL);
	arr = ft_split(new, '\31');
	free(new);
	return (arr);
}

static char	*mod_s(char *s, char *map, int include_quotes)
{
	int		i;
	char	*new;

	new = ft_calloc(1, ft_strlen(s) + 1);
	if (new == NULL)
	{
		free (map);
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (map[i] == '1' || (map[i] == '2' && include_quotes))
			ft_strlcat(new, s + i, ft_strlen(new) + 2);
		else if (map[i] == '0')
			ft_strlcat(new, "\31", ft_strlen(new) + 2);
		i++;
	}
	free(map);
	return (new);
}

char	*parse_s(char *s)
{
	char	*map;

	map = ft_calloc(1, ft_strlen(s) + 1);
	if (map == NULL)
		return (NULL);
	enumerate_map(s, map);
	return (map);
}

void	enumerate_map(char *s, char *map)
{
	char	flag;
	int		i;

	i = 0;
	flag = '\0';
	while (s[i] != '\0')
	{
		if (ft_isspace((int)s[i]) && !flag)
			map[i] = '0';
		else if ((s[i] == '"' || s[i] == '\'') && (!flag || s[i] == flag))
		{
			if (!flag && is_last_quote(s, i))
				map[i] = '1';
			else
				map[i] = '2';
			if (!flag)
				flag = s[i];
			else
				flag = '\0';
		}
		else
			map[i] = '1';
		i++;
	}
	map[i] = '\0';
}

int	is_last_quote(char *s, int i)
{
	char	quote;

	quote = s[i];
	if (quote != '\'' && quote != '"')
		return (0);
	if (ft_strrchr(s, (int)quote) == s + i)
		return (1);
	return (0);
}
