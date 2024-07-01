/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:06 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/03 23:41:38 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_infile(t_cmd *cmd, t_word *redirect);
static int	handle_outfile(t_cmd *cmd, t_word *redirect);

int	get_fds(t_data *data, t_cmd *command)
{
	t_word	*redir;

	(void) data;
	redir = command->redirects;
	errno = 0;
	while (redir)
	{
		if (redir->type == T_INFILE || redir->type == T_HEREDOC_LIM)
			errno = handle_infile(command, redir);
		else if (redir->type == T_OUTFILE_AP || redir->type == T_OUTFILE_TR)
			errno = handle_outfile(command, redir);
		if (errno)
		{
			perror(redir->word);
			return (FILE_ERROR);
		}
		redir = redir->next;
	}
	return (NO_ERROR);
}

static int	handle_infile(t_cmd *cmd, t_word *redirect)
{
	char	*infile;
	int		fd_in;

	if (redirect->type == T_HEREDOC_LIM && !redirect->is_fd)
		return (NO_ERROR);
	infile = redirect->word;
	errno = 0;
	if (redirect->type == T_INFILE)
	{
		fd_in = open(infile, O_RDONLY);
		if (errno)
			return (errno);
	}
	if (redirect->is_fd)
	{
		if (redirect->type == T_HEREDOC_LIM)
			fd_in = redirect->is_fd;
		if (cmd->saved_fd_in == STDIN_FILENO)
			cmd->saved_fd_in = fd_in;
		dup2(fd_in, STDIN_FILENO);
	}
	close(fd_in);
	return (NO_ERROR);
}

static int	handle_outfile(t_cmd *cmd, t_word *redirect)
{
	char	*outfile;
	int		fd_out;

	outfile = redirect->word;
	if (redirect->type == T_OUTFILE_AP)
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (errno)
		return (errno);
	if (!redirect->is_fd)
	{
		if (redirect->type == T_OUTFILE_TR)
			write(fd_out, "", 0);
	}
	else
	{
		if (cmd->saved_fd_out == STDOUT_FILENO)
			cmd->saved_fd_out = fd_out;
		dup2(fd_out, STDOUT_FILENO);
	}
	close(fd_out);
	return (NO_ERROR);
}
