/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 04:32:31 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 03:34:18 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

void	init_main(t_data *data, char **envp)
{
	data->is_exit = false;
	data->path = NULL;
	data->line = NULL;
	data->groups = NULL;
	data->envp = envpcpy(envp);
	if (!data->envp)
		exit(1);
	update_pwd(data);
	data->commands = NULL;
	data->temp_files = NULL;
	data->exit_status = NO_ERROR;
	data->new_exit_status = NO_ERROR;
	data->error = NO_ERROR;
	data->pipe1[0] = STDIN_FILENO;
	data->pipe2[0] = STDIN_FILENO;
	data->pipe1[1] = STDOUT_FILENO;
	data->pipe2[1] = STDOUT_FILENO;
	data->saved_stderr = STDERR_FILENO;
	data->saved_stdin = STDIN_FILENO;
}

void	clear_and_exit(t_data *data)
{
	rl_clear_history();
	free_2d(data->envp);
	exit(data->exit_status);
}

void	signals_and_prompt(t_data *data)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	data->path = line_pwd();
	if (!data->path)
		clean_and_exit(data, MALLOC_MSG);
	data->line = readline(data->path);
	if (g_flag == true)
	{
		g_flag = false;
		data->exit_status = INTRPT_CODE;
	}
	if (!data->line)
	{
		data->line = ft_strdup("exit");
		if (!data->line)
			clean_and_exit(data, MALLOC_MSG);
	}
}

int	count_heredocs_needed(t_data *data)
{
	t_cmd	*cmd;
	t_word	*redirects;
	int		i;

	i = 0;
	cmd = data->commands;
	while (cmd)
	{
		redirects = cmd->redirects;
		while (redirects)
		{
			if (redirects->type == T_HEREDOC_LIM && redirects->is_fd)
				i++;
			redirects = redirects -> next;
		}
		cmd = cmd-> next;
	}
	if (i)
		return (i + 3);
	return (i);
}

bool	parse_and_execute(t_data *data)
{
	add_history(data->line);
	data->new_exit_status = initial_parsing(data);
	if (data->line[0] == '\0')
	{
		free(data->path);
		free(data->line);
		return (true);
	}
	if (data->new_exit_status)
	{
		data->exit_status = data->new_exit_status;
		data->new_exit_status = NO_ERROR;
		free(data->path);
		free(data->line);
		ft_putstr_fd(" parsing error\n", STDERR_FILENO);
		return (true);
	}
	parse(data, data->line);
	data->new_exit_status = exec_start(data);
	free_commands(&data->commands);
	free_temp_files(&data->temp_files);
	data->exit_status = data->new_exit_status;
	data->new_exit_status = NO_ERROR;
	return (false);
}
