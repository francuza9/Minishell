/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:23 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 21:37:03 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_oldpwd(t_data *data)
{
	char	*temp_1;
	char	*temp_2;
	char	**new_envp;

	unset_var(data, "OLDPWD");
	temp_1 = find_env_value(data, "PWD");
	if (temp_1 == NULL)
		return ;
	temp_2 = ft_strjoin("OLDPWD=", temp_1);
	free(temp_1);
	if (temp_2 == NULL)
	{
		data->error = MALLOC_ERR;
		return ;
	}
	new_envp = handle_array(data->envp, temp_2);
	if (new_envp == NULL)
	{
		free(temp_2);
		data->error = MALLOC_ERR;
		return ;
	}
	free(data->envp);
	data->envp = new_envp;
}

static char	*find_path(t_data *data, char *home, char *path)
{
	int	i;

	i = 0;
	home = NULL;
	while (data->envp[i])
	{
		if (!(ft_strncmp(path, data->envp[i], ft_strlen(path))))
		{
			home = ft_substr(data->envp[i], ft_strlen(path), \
			ft_strlen(data->envp[i]) - (ft_strlen(path) - 1));
			break ;
		}
		i++;
	}
	if (data->envp[i] == NULL)
	{
		write(STDERR_FILENO, path, ft_strlen(path) - 1);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
	}
	else if (home == NULL)
		data->error = MALLOC_ERR;
	return (home);
}

int	cd_errs(char *path)
{
	ft_putstr_fd(path, STDERR_FILENO);
	if (!access(path, F_OK))
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

char	*go_path(t_data *data, char *dif_path, char *path, t_cmd *cmd)
{
	dif_path = find_path(data, dif_path, path);
	if (!dif_path)
		return (NULL);
	if (chdir(dif_path) == -1)
	{
		cd_errs(dif_path);
		free(dif_path);
		data->new_exit_status = 1;
		return (NULL);
	}
	if (!(ft_strncmp(path, "OLDPWD=", 7)))
		ft_pwd(data, cmd);
	return (dif_path);
}

int	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*dif_path;
	int		i;

	i = 0;
	dif_path = NULL;
	while (cmd->argv[i])
		i++;
	if (i > 2)
		return (exit_cd());
	if (i == 1 || (i == 2 && !ft_strncmp(cmd->argv[1], "--", 3)))
		dif_path = go_path(data, dif_path, "HOME=", cmd);
	else if (i == 2 && !ft_strncmp(cmd->argv[1], "-", 2))
		dif_path = go_path(data, dif_path, "OLDPWD=", cmd);
	else if (chdir(cmd->argv[1]) == -1)
		return (cd_errs(cmd->argv[1]));
	if (!data->new_exit_status)
	{
		update_oldpwd(data);
		update_pwd(data);
	}
	free(dif_path);
	return (data->new_exit_status);
}
