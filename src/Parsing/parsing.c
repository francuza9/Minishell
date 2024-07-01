/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:21 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 06:58:53 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	send_words(t_data *data, t_cmd *cmd, t_word *word)
{
	t_word	*temp;

	temp = word;
	if (!word)
		return ;
	set_prios(word);
	while (temp)
	{
		parse_word(data, cmd, temp);
		handle_errors(data);
		temp = temp -> next;
	}
	free_words(&word);
}

void	split_by_pipes(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_inside(str, i);
		if (str[i] == '|')
			str[i] = '\31';
		i++;
	}
	data->groups = ft_split(str, '\31');
}

void	parse(t_data *data, char *str)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	split_by_pipes(data, str);
	if (!data->groups)
		clean_and_exit(data, MALLOC_MSG);
	while (data->groups[i])
	{
		if (!append_command(&data->commands))
			clean_and_exit(data, MALLOC_MSG);
		cmd = find_last_command(data->commands);
		parse_string(data, cmd, data->groups[i]);
		i++;
	}
	data->pipe_count = i - 1;
	free_2d(data->groups);
	data->groups = NULL;
	if (data->error)
		clean_and_exit(data, MALLOC_MSG);
}
