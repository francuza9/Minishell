/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:10:17 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/07 02:59:53 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_path(t_cmd *cmd);
static int	find_valid_path(t_cmd *cmd, char **paths);

int	get_command_path(t_data *data, t_cmd *cmd)
{
	char	*paths_line;
	char	**paths;

	if (!cmd->argv[0][0] || !ft_strncmp(cmd->argv[0], "..", 3) \
	|| !ft_strncmp(cmd->argv[0], ".", 2))
	{
		cmd->err_msg = ft_strjoin(cmd->argv[0], CMD_NOT_FOUND);
		return (CMD_NFND_ERR);
	}
	if (ft_strchr(cmd->argv[0], '/'))
		return (check_path(cmd));
	paths_line = find_env_value(data, "PATH");
	if (paths_line)
	{
		paths = ft_split(paths_line, ':');
		free(paths_line);
	}
	else
	{
		cmd->err_msg = ft_strjoin(cmd->argv[0], CMD_NOT_FOUND);
		return (CMD_NFND_ERR);
	}
	if (!paths)
		return (MALLOC_ERR);
	return (find_valid_path(cmd, paths));
}

static int	check_path(t_cmd *cmd)
{
	DIR	*dir;

	dir = opendir(cmd->argv[0]);
	if (dir)
	{
		closedir(dir);
		cmd->err_msg = ft_strjoin(cmd->argv[0], IS_A_DIR_MSG);
		return (IS_A_DIR_ERR);
	}
	if (access(cmd->argv[0], F_OK) == -1)
	{
		cmd->err_msg = ft_strjoin(cmd->argv[0], NO_SUCH_FILE);
		return (NO_SUCH_F_ERR);
	}
	if (access(cmd->argv[0], X_OK) == -1)
	{
		cmd->err_msg = ft_strjoin(cmd->argv[0], PERM_DENIED);
		return (PERM_DNIED_ERR);
	}
	cmd->path = ft_strdup(cmd->argv[0]);
	return (NO_ERROR);
}

static int	find_valid_path(t_cmd *cmd, char **paths)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = temp;
		cmd->path = ft_strjoin(paths[i], cmd->argv[0]);
		if (cmd->path && access(cmd->path, X_OK) == 0)
			break ;
		free(cmd->path);
		i++;
	}
	if (!paths[i])
	{
		free_2d(paths);
		cmd->path = NULL;
		cmd->err_msg = ft_strjoin(cmd->argv[0], CMD_NOT_FOUND);
		return (CMD_NFND_ERR);
	}
	free_2d(paths);
	return (NO_ERROR);
}
