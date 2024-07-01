/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:25:29 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 03:49:25 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_nls(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)data;
	while (cmd -> argv[i])
		i++;
	if (i != 1)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	i++;
}

char	*get_real_pwd(t_data *data)
{
	char	*buffer;
	char	*temp;
	int		i;

	buffer = NULL;
	i = 0;
	while (i < 15000)
	{
		temp = getcwd(buffer, i);
		if (temp != NULL)
		{
			free(temp);
			buffer = getcwd(buffer, i);
			break ;
		}
		free(temp);
		i += 10;
	}
	if (!buffer)
		data->error = MALLOC_ERR;
	return (buffer);
}

int	exit_cd(void)
{
	ft_putstr_fd(" too many arguments\n", 2);
	return (1);
}

void	update_pwd(t_data *data)
{
	char	*temp_1;
	char	*temp_2;
	char	**new_envp;

	unset_var(data, "PWD");
	temp_1 = get_real_pwd(data);
	if (temp_1 == NULL)
		return ;
	temp_2 = ft_strjoin("PWD=", temp_1);
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
