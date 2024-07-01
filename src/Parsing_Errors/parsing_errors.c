/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:13 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/07 23:36:46 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_filename(char *str, int i)
{
	int	j;

	while (ft_isspace(str[i]))
		i++;
	j = i;
	while (!ft_isdelimiter(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_inside(str, i);
		i++;
	}
	if (j == i)
		return (-1);
	return (i);
}

bool	handle_pipe(char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|' || str[i] == '\0')
		return (true);
	return (false);
}

int	redirect_errors(t_data *data, char *str, int heredocs, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_inside(str, i);
		if ((str[i] == '<' && str[i + 1] == '<') \
		|| (str[i] == '>' && str[i + 1] == '>'))
		{
			if (str[i] == '<')
				heredocs++;
			i = valid_filename(str, i + 2);
			if (i == -1)
				return (2);
			continue ;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			i = valid_filename(str, i + 1);
			if (i == -1)
				return (2);
			continue ;
		}
		i++;
	}
	check_max_heredocs(data, str, heredocs);
	return (0);
}

int	syntax_errors(t_data *data, char *str)
{
	int		i;
	int		heredocs;

	heredocs = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_inside(str, i);
		if ((i == -1) || str[i] == '&' \
		|| (str[i] == '|' && str[i + 1] == '|') \
		|| (str[0] == '|' || str[ft_strlen(str) - 1] == '|') \
		|| (str[i] == '(' || str[i] == ')'))
			return (2);
		if (str[i] == '|' && handle_pipe(str, i + 1))
			return (2);
		i++;
	}
	if (redirect_errors(data, str, heredocs, 0) >= 1)
		return (2);
	return (0);
}

int	initial_parsing(t_data *data)
{
	char	*trimmed;
	int		i;
	int		exit_stat;

	i = 0;
	if (check_open_quotes(data->line) == -1)
		return (2);
	trimmed = ft_strtrim(data->line, " \t\n\v\f\r");
	if (!trimmed)
		clean_and_exit(data, MALLOC_MSG);
	free(data->line);
	data->line = trimmed;
	ignore_comment(&data->line);
	if (!data->line)
		clean_and_exit(data, MALLOC_MSG);
	exit_stat = syntax_errors(data, data->line);
	return (exit_stat);
}
