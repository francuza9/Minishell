/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 02:44:43 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/09 07:02:46 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

int	exec_start(t_data *data)
{
	int	errno;

	errno = 0;
	signal(SIGINT, &sig_handler_doc);
	handle_errors(data);
	collect_heredocs(data);
	handle_errors(data);
	if (g_flag == true)
	{
		g_flag = false;
		return (INTRPT_CODE);
	}
	signal(SIGQUIT, &sig_handler_dump);
	signal(SIGINT, &sig_handler_int);
	if (!data->pipe_count)
		errno = exec_single_command(data);
	else
		errno = exec_piped_commands(data, data->commands);
	close_heredoc_fds(data, NULL);
	handle_errors(data);
	return (errno);
}

void	handle_errors(t_data *data)
{
	if (data->error == MALLOC_ERR)
		clean_and_exit(data, MALLOC_MSG);
	if (data->error == NO_FD_ERR)
		clean_and_exit(data, N_ENOUGH_FDS);
}
