/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:10:59 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 06:58:36 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	color_prompt(char *buffer, char **prompt, int i)
{
	ft_strlcat(*prompt, "\1\033[1;93m\2", 10);
	buffer = getcwd(buffer, i);
	ft_strlcat(*prompt, buffer, ft_strlen(*prompt) + i);
	free(buffer);
	ft_strlcat(*prompt, "$: \1\033[0m\2", ft_strlen(*prompt) + 10);
}

char	*line_pwd(void)
{
	int		i;
	char	*prompt;
	char	*buffer;

	i = 0;
	while (i < 15000)
	{
		buffer = malloc(i);
		if (!buffer)
			return (NULL);
		if (getcwd(buffer, i))
			break ;
		free(buffer);
		i++;
	}
	prompt = ft_calloc(sizeof(char), i + 18);
	if (!prompt || !buffer)
	{
		free(buffer);
		free(prompt);
		return (NULL);
	}
	color_prompt(buffer, &prompt, i);
	return (prompt);
}

int	call_commands(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp(cmd -> argv[0], "cd", 3))
		data->new_exit_status = ft_cd(data, cmd);
	else if (!ft_strncmp(cmd -> argv[0], "echo", 5))
		data->new_exit_status = ft_echo(data, cmd);
	else if (!ft_strncmp(cmd -> argv[0], "unset", 6))
		data->new_exit_status = ft_unset(data, cmd);
	else if (!ft_strncmp(cmd -> argv[0], "pwd", 4))
		data->new_exit_status = ft_pwd(data, cmd);
	else if (!ft_strncmp(cmd -> argv[0], "exit", 5))
		ft_exit(data, cmd);
	else if (!ft_strncmp(cmd -> argv[0], "env", 4))
		data->new_exit_status = ft_env(data, cmd);
	else if (!ft_strncmp(cmd -> argv[0], "export", 7))
		ft_export(data, cmd);
	return (data->new_exit_status);
}

char	**envpcpy(char	**envp)
{
	char	**temp;
	int		lines;
	int		i;

	lines = 0;
	while (envp[lines])
		lines++;
	temp = malloc (sizeof(char *) * (lines + 1));
	if (!temp)
		return (NULL);
	lines = 0;
	while (envp[lines])
	{
		i = 0;
		while (envp[lines][i])
			i++;
		temp[lines] = malloc (sizeof(char) * i + 1);
		if (!temp[lines])
			break ;
		ft_strlcpy(temp[lines], envp[lines], i + 1);
		lines++;
	}
	temp[lines] = NULL;
	return (temp);
}
