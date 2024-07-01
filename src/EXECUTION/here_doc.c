/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:20:05 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/07 03:03:34 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

static void	handle_heredocs(t_data *data, t_cmd *cmd);
static void	here_doc(t_data *data, char *limiter, int fd, bool here_doc_vars);
static void	dummy_here_doc(char	*limiter);
static bool	check_dup_errors(t_data *data);

void	collect_heredocs(t_data *data)
{
	t_cmd		*cmd;

	data->saved_stderr = dup(STDERR_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	if (check_dup_errors(data))
		clean_and_exit(data, N_ENOUGH_FDS);
	cmd = data->commands;
	while (cmd)
	{
		handle_heredocs(data, cmd);
		if (data->error)
			break ;
		cmd = cmd->next;
	}
	if (g_flag == true)
	{
		close_heredoc_fds(data, NULL);
		dup2(data->saved_stderr, STDERR_FILENO);
		dup2(data->saved_stdin, STDIN_FILENO);
	}
	close(data->saved_stderr);
	close(data->saved_stdin);
}

static void	handle_heredocs(t_data *data, t_cmd *cmd)
{
	t_word	*redir;
	int		fd_write;

	redir = cmd->redirects;
	while (redir && !g_flag)
	{
		if (redir->type == T_HEREDOC_LIM)
		{
			if (!redir->is_fd)
				dummy_here_doc(redir->word);
			else
			{
				redir->is_fd = create_temp_file(data, &fd_write);
				if (redir->is_fd == -1)
					return ;
				here_doc(data, redir->word, fd_write, cmd->here_doc_vars);
				close(fd_write);
			}
		}
		redir = redir->next;
	}
}

static void	here_doc(t_data *data, char *limiter, int fd, bool here_doc_vars)
{
	char		*temp;
	char		*new_line;

	while (1)
	{
		temp = readline("> ");
		if (temp == NULL)
		{
			print_heredoc_warning(limiter);
			return ;
		}
		if (ft_strlen(temp) == ft_strlen(limiter) && \
		!ft_strncmp(temp, limiter, ft_strlen(limiter)))
		{
			free(temp);
			break ;
		}
		new_line = ft_strjoin(temp, "\n");
		free(temp);
		if (here_doc_vars)
			new_line = heredoc_env_vars(data, new_line);
		if (new_line)
			write(fd, new_line, ft_strlen(new_line));
		free(new_line);
	}
}

static void	dummy_here_doc(char	*limiter)
{
	char	*new_line;

	while (1)
	{
		new_line = readline("> ");
		if (new_line == NULL)
		{
			print_heredoc_warning(limiter);
			return ;
		}
		if (ft_strlen(new_line) == ft_strlen(limiter) && \
		!ft_strncmp(new_line, limiter, ft_strlen(limiter)))
		{
			free(new_line);
			break ;
		}
		free(new_line);
	}
}

static bool	check_dup_errors(t_data *data)
{
	if (data->saved_stderr == -1 || data->saved_stdin == -1)
	{
		if (data->saved_stderr != -1)
			close(data->saved_stderr);
		if (data->saved_stdin != -1)
			close(data->saved_stdin);
		return (NO_FD_ERR);
	}
	return (NO_ERROR);
}
