/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:11 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 22:47:13 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_inside(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

bool	ft_isdelimiter(char c)
{
	if (c == '|' || c == '<' || c == '>' \
	|| ft_isspace(c) || c == '\0')
		return (true);
	return (false);
}

int	check_open_quotes(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_inside(str, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}

void	ignore_comment(char **line)
{
	char	*temp;
	int		i;

	i = 0;
	if ((*line)[0] == '#')
	{
		free(*line);
		*line = ft_strdup("");
		return ;
	}
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i = skip_inside(*line, i);
		if ((*line)[i] == '#' && (i && ((ft_isspace((*line)[i - 1])) \
		|| (*line)[i - 1] == '|')))
		{
			temp = ft_substr(*line, 0, i);
			free(*line);
			*line = temp;
			return ;
		}
		i++;
	}
}

void	check_max_heredocs(t_data *data, char *str, int heredocs)
{
	if (heredocs > 16)
	{
		free(str);
		free(data->path);
		free_2d(data->envp);
		ft_putstr_fd(" too many heredocs.\n", 2);
		exit(2);
	}
}
