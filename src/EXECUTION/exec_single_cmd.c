/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:57:23 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/09 06:58:23 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

static int	exec_single_child(t_data *data);
static int	exec_single_builtin(t_data *data);
static void	restore_std_fileno(t_data *data);
static bool	check_dup_errors(t_data *data);

int	exec_single_command(t_data *data)
{
	pid_t	pid;
	int		error;

	if (data->commands->argv && is_builtin(data->commands->argv[0]))
		return (exec_single_builtin(data));
	pid = fork();
	if (pid == -1)
		clean_and_exit(data, strerror(errno));
	if (pid == 0)
	{
		error = exec_single_child(data);
		child_cleanup(data, error);
	}
	return (wait_last_child(pid));
}

static int	exec_single_child(t_data *data)
{
	int	error;

	error = get_fds(data, data->commands);
	if (error)
		return (error);
	else if (data->commands->err_msg)
	{
		write(STDERR_FILENO, data->commands->err_msg, \
		ft_strlen(data->commands->err_msg));
		return (AMB_RDRCT_ERR);
	}
	if (!data->commands->argv)
		return (NO_ERROR);
	error = get_command_path(data, data->commands);
	if (error)
	{
		if (!data->commands->err_msg)
			clean_and_exit(data, MALLOC_MSG);
		write(STDERR_FILENO, data->commands->err_msg, \
		ft_strlen(data->commands->err_msg));
		return (error);
	}
	execve(data->commands->path, data->commands->argv, data->envp);
	perror("execve");
	return (errno);
}

static int	exec_single_builtin(t_data *data)
{
	int	error;

	data->commands->saved_fd_in = dup(STDIN_FILENO);
	data->commands->saved_fd_out = dup(STDOUT_FILENO);
	if (check_dup_errors(data))
		clean_and_exit(data, N_ENOUGH_FDS);
	error = get_fds(data, data->commands);
	if (error || data->commands->err_msg)
		restore_std_fileno(data);
	if (error)
		return (error);
	else if (data->commands->err_msg)
	{
		write(STDERR_FILENO, data->commands->err_msg, \
		ft_strlen(data->commands->err_msg));
		return (AMB_RDRCT_ERR);
	}
	error = call_commands(data, data->commands);
	restore_std_fileno(data);
	return (error);
}

static void	restore_std_fileno(t_data *data)
{
	if (data->commands->saved_fd_in != STDIN_FILENO)
	{
		dup2(data->commands->saved_fd_in, STDIN_FILENO);
		close(data->commands->saved_fd_in);
	}
	if (data->commands->saved_fd_out != STDOUT_FILENO)
	{
		dup2(data->commands->saved_fd_out, STDOUT_FILENO);
		close(data->commands->saved_fd_out);
	}
}

static bool	check_dup_errors(t_data *data)
{
	if (data->commands->saved_fd_in == -1 || data->commands->saved_fd_out == -1)
	{
		if (data->commands->saved_fd_in != -1)
			close(data->commands->saved_fd_in);
		if (data->commands->saved_fd_out != -1)
			close(data->commands->saved_fd_out);
		return (NO_FD_ERR);
	}
	return (NO_ERROR);
}
