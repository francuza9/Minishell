/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_temp_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 04:28:38 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/07 03:03:45 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	temp_file_fds(t_data *data, char *filename, int *fd_write)
{
	int	fd_read;

	if (filename == NULL)
		return (-1);
	*fd_write = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_write == -1)
	{
		data->error = NO_FD_ERR;
		return (-1);
	}
	fd_read = open(filename, O_RDONLY);
	if (fd_read == -1)
	{
		data->error = NO_FD_ERR;
		unlink(filename);
		close(*fd_write);
		return (-1);
	}
	if (!append_node(&data->temp_files, filename))
		data->error = MALLOC_ERR;
	return (fd_read);
}

char	*get_filename(t_data *data, int i)
{
	char	*temp;
	char	*filename;

	temp = ft_itoa(i);
	if (!temp)
		data->error = MALLOC_ERR;
	filename = ft_strjoin("heredoc_", temp);
	if (!filename)
		data->error = MALLOC_ERR;
	free(temp);
	return (filename);
}

int	create_temp_file(t_data *data, int *fd_write)
{
	int		i;
	int		fd_read;
	char	*filename;

	i = 0;
	while (1)
	{
		filename = get_filename(data, i);
		if (!filename)
			break ;
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
		i++;
	}
	if (!filename)
		return (-1);
	fd_read = temp_file_fds(data, filename, fd_write);
	if (fd_read == -1)
		free(filename);
	return (fd_read);
}
