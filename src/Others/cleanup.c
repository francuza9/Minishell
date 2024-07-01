/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:32:05 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/09 07:02:50 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_cleanup(t_data *data, int exit_status)
{
	if (data->pipe1[0] != STDIN_FILENO)
		close(data->pipe1[0]);
	if (data->pipe2[0] != STDIN_FILENO)
		close(data->pipe2[0]);
	if (data->pipe1[1] != STDOUT_FILENO)
		close(data->pipe1[1]);
	if (data->pipe2[1] != STDOUT_FILENO)
		close(data->pipe2[1]);
	data->pipe1[0] = STDIN_FILENO;
	data->pipe2[0] = STDIN_FILENO;
	data->pipe1[1] = STDOUT_FILENO;
	data->pipe2[1] = STDOUT_FILENO;
	close_heredoc_fds(data, NULL);
	free_commands(&data->commands);
	free_temp_files(&data->temp_files);
	free_2d(data->envp);
	data->envp = NULL;
	free(data->line);
	data->line = NULL;
	free(data->path);
	data->path = NULL;
	exit(exit_status);
}

void	clean_and_exit(t_data *data, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	rl_clear_history();
	if (data->pipe1[0] != STDIN_FILENO)
		close(data->pipe1[0]);
	if (data->pipe2[0] != STDIN_FILENO)
		close(data->pipe2[0]);
	if (data->pipe1[1] != STDOUT_FILENO)
		close(data->pipe1[1]);
	if (data->pipe2[1] != STDOUT_FILENO)
		close(data->pipe2[1]);
	data->pipe1[0] = STDIN_FILENO;
	data->pipe2[0] = STDIN_FILENO;
	data->pipe1[1] = STDOUT_FILENO;
	data->pipe2[1] = STDOUT_FILENO;
	free_2d(data->groups);
	close_heredoc_fds(data, NULL);
	free_commands(&data->commands);
	free_temp_files(&data->temp_files);
	free_2d(data->envp);
	free(data->line);
	free(data->path);
	exit(EXIT_FAILURE);
}

void	free_words(t_word **words)
{
	t_word	*current;
	t_word	*next;

	if (!*words)
		return ;
	current = *words;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	*words = NULL;
}

void	free_temp_files(t_node **temp_files)
{
	t_node	*current;
	t_node	*next;

	if (*temp_files == NULL)
		return ;
	current = *temp_files;
	while (current)
	{
		next = current->next;
		unlink(current->str);
		free(current->str);
		free(current);
		current = next;
	}
	*temp_files = NULL;
}

void	free_commands(t_cmd **commands)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!*commands)
		return ;
	current = *commands;
	while (current)
	{
		next = current -> next;
		free_2d(current->argv);
		free(current->path);
		free(current->err_msg);
		free_words(&current->redirects);
		free(current);
		current = next;
	}
	*commands = NULL;
}
