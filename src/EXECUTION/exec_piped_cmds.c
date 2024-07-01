/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 00:33:53 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/04 00:33:58 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

static void	exec_cmd(t_data *data, t_cmd *cmd);
static void	handle_first_cmd(t_data *data, t_cmd *cmd);
static void	handle_cmd(t_data *data, t_cmd *cmd, int i);
static int	handle_last_cmd(t_data *data, t_cmd *cmd);

int	exec_piped_commands(t_data *data, t_cmd *commands)
{
	int		i;
	int		error;

	i = 0;
	while (i <= data->pipe_count)
	{
		if (i == 0)
			handle_first_cmd(data, commands);
		else if (i == data->pipe_count)
			error = handle_last_cmd(data, commands);
		else
			handle_cmd(data, commands, i);
		i++;
	}
	while (wait(NULL) > 0)
		;
	if (g_flag == true)
		g_flag = false;
	return (error);
}

static void	exec_cmd(t_data *data, t_cmd *cmd)
{
	int	err;

	if (cmd->err_msg)
	{
		write(STDERR_FILENO, cmd->err_msg, ft_strlen(cmd->err_msg));
		child_cleanup(data, AMB_RDRCT_ERR);
	}
	if (!cmd->argv)
		child_cleanup(data, EXIT_SUCCESS);
	if (is_builtin(cmd->argv[0]))
	{
		err = call_commands(data, cmd);
		child_cleanup(data, err);
	}
	err = get_command_path(data, cmd);
	if (err)
	{
		write(STDERR_FILENO, cmd->err_msg, ft_strlen(cmd->err_msg));
		child_cleanup(data, err);
	}
	close_heredoc_fds(data, cmd);
	execve(cmd->path, cmd->argv, data->envp);
	perror(cmd->argv[0]);
	child_cleanup(data, errno);
}

static void	handle_first_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	if (pipe(data->pipe1) == -1)
		clean_and_exit(data, strerror(errno));
	pid = fork();
	if (pid == -1)
		clean_and_exit(data, strerror(errno));
	if (pid == 0)
	{
		errno = get_fds(data, data->commands);
		if (errno)
			child_cleanup(data, errno);
		close (data->pipe1[0]);
		if (cmd->saved_fd_out == STDOUT_FILENO)
			dup2(data->pipe1[1], STDOUT_FILENO);
		else
			close(cmd->saved_fd_out);
		close(data->pipe1[1]);
		exec_cmd(data, cmd);
	}
	close(data->pipe1[1]);
}

static void	handle_cmd(t_data *data, t_cmd *cmd, int i)
{
	pid_t	pid;

	while (i--)
		cmd = cmd->next;
	if (pipe(data->pipe2) == -1)
		clean_and_exit(data, strerror(errno));
	pid = fork();
	if (pid == -1)
		clean_and_exit(data, strerror(errno));
	if (pid == 0)
	{
		errno = get_fds(data, cmd);
		if (errno)
			child_cleanup(data, errno);
		handle_piping(data, cmd);
		exec_cmd(data, cmd);
	}
	close(data->pipe1[0]);
	close(data->pipe2[1]);
	data->pipe1[0] = data->pipe2[0];
}

static int	handle_last_cmd(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	while (cmd->next)
		cmd = cmd->next;
	pid = fork();
	if (pid == -1)
		clean_and_exit(data, strerror(errno));
	if (pid == 0)
	{
		errno = get_fds(data, cmd);
		if (errno)
			child_cleanup(data, errno);
		if (cmd->saved_fd_in == STDIN_FILENO)
			dup2(data->pipe1[0], STDIN_FILENO);
		else
			close (cmd->saved_fd_in);
		close(data->pipe1[0]);
		exec_cmd(data, cmd);
	}
	close(data->pipe1[0]);
	return (wait_last_child(pid));
}
