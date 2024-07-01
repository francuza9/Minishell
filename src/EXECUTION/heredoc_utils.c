/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:06:29 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/07 03:04:00 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_heredoc_fds(t_data *data, t_cmd *exception_cmd)
{
	t_word	*redir;
	t_cmd	*cmd;

	cmd = data->commands;
	while (cmd)
	{
		if (cmd == exception_cmd)
		{
			cmd = cmd->next;
			continue ;
		}
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == T_HEREDOC_LIM)
			{
				if (redir->is_fd && redir->is_fd > 1)
					close(redir->is_fd);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

char	*heredoc_env_vars(t_data *data, char *temp)
{
	int		i;
	char	*s;
	char	*new_line;

	if (!temp)
		return (NULL);
	s = temp;
	new_line = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$')
		{
			new_line = append_to_buffer(data, new_line, s, i);
			s = handle_env_var(data, &new_line, s + i);
			if (s == NULL)
				break ;
			i = 0;
		}
		else
			i++;
	}
	new_line = append_to_buffer(data, new_line, s, i);
	free(temp);
	return (new_line);
}

void	print_heredoc_warning(char *limiter)
{
	write(STDERR_FILENO, "warning: ", 9);
	write(STDERR_FILENO, HERE_WARNING, ft_strlen(HERE_WARNING));
	write(STDERR_FILENO, limiter, ft_strlen(limiter));
	write(STDERR_FILENO, "')\n", 3);
}
