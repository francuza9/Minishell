/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:27:58 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/04 19:28:05 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_spaces(char *s)
{
	while (*s != '\0')
	{
		if (ft_isspace(*s))
			return (true);
		s++;
	}
	return (false);
}

int	check_var_char(char c)
{
	if (ft_isalnum((int) c))
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

char	*remove_leading_spaces(char *buffer, int j)
{
	char	*temp;
	char	*new;
	int		i;

	i = j;
	while (ft_isspace(buffer[i]))
		i++;
	if (i != 0 && ft_isspace(buffer[i - 1]))
		i--;
	temp = ft_substr(buffer, 0, j);
	if (!temp[0])
		new = strdup(buffer + i + 1);
	else
		new = ft_strjoin(temp, buffer + i);
	free(temp);
	free(buffer);
	return (new);
}
