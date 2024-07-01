/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:05:12 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/03 23:44:33 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

bool	is_builtin(char *command)
{
	if (!ft_strncmp(command, "cd", 3))
		return (true);
	else if (!ft_strncmp(command, "echo", 5))
		return (true);
	else if (!ft_strncmp(command, "unset", 6))
		return (true);
	else if (!ft_strncmp(command, "pwd", 4))
		return (true);
	else if (!ft_strncmp(command, "exit", 5))
		return (true);
	else if (!ft_strncmp(command, "env", 4))
		return (true);
	else if (!ft_strncmp(command, "export", 7))
		return (true);
	return (false);
}

void	handle_piping(t_data *data, t_cmd *cmd)
{
	close(data->pipe2[0]);
	if (cmd->saved_fd_in == STDIN_FILENO)
		dup2(data->pipe1[0], STDIN_FILENO);
	else
		close(cmd->saved_fd_in);
	close(data->pipe1[0]);
	if (cmd->saved_fd_out == STDOUT_FILENO)
		dup2(data->pipe2[1], STDOUT_FILENO);
	else
		close(cmd->saved_fd_out);
	close(data->pipe2[1]);
}

int	wait_last_child(pid_t pid)
{
	int	status;

	status = NO_ERROR;
	waitpid(pid, &status, 0);
	if (g_flag == true)
	{
		g_flag = false;
		return (INTRPT_CODE);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			return (CORE_DUMPED);
		else
			return (WTERMSIG(status));
	}
	return (NO_ERROR);
}
