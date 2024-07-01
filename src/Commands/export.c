/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:40 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 20:34:35 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	replace(t_data *data, char *argv)
{
	char	*new;
	char	*temp;
	int		i;
	int		pos;

	pos = 0;
	i = 0;
	temp = NULL;
	while (argv[pos] && argv[pos] != '=')
		pos++;
	if (!argv[pos])
		return ;
	temp = ft_substr(argv, 0, pos);
	if (!temp)
		return ;
	while (ft_strncmp(temp, data -> envp[i], pos))
		i++;
	free(temp);
	new = malloc(sizeof(char) * ft_strlen(argv) + 1);
	if (!new)
		return ;
	ft_strlcpy(new, argv, ft_strlen(argv) + 1);
	free(data->envp[i]);
	data->envp[i] = new;
}

bool	append_true(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '=' && argv[i] != '\0')
		i++;
	if (argv[i] == '=' && argv[i - 1] == '+')
		return (true);
	return (false);
}

void	append_to_line(t_data *data, char *argv)
{
	char	*new;
	char	*temp;
	int		i;
	int		pos;

	pos = (int)(ft_strchr(argv, '+') - argv);
	temp = ft_substr(argv, 0, pos);
	if (!temp)
		return ;
	i = 0;
	while (ft_strncmp(temp, data->envp[i], pos))
		i++;
	free(temp);
	if (data -> envp[i][pos] == '=')
		pos++;
	temp = ft_substr(argv, pos + 1, ft_strlen(argv) - pos);
	if (!temp)
		return ;
	new = ft_strjoin(data -> envp[i], temp);
	free(temp);
	if (!new)
		return ;
	free(data->envp[i]);
	data->envp[i] = new;
}

void	declare_vars(t_data *data, t_cmd *cmd)
{
	int		i;

	if (ft_strlen(cmd->argv[1]) > 1 && cmd->argv[1][0] == '-')
	{
		export_invalid(data, cmd->argv[1]);
		return ;
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (var_errors(data, cmd->argv[i]))
			;
		else if (already_exist(data, cmd->argv[i]) && append_true(cmd->argv[i]))
			append_to_line(data, cmd->argv[i]);
		else if (already_exist(data, cmd->argv[i]))
			replace(data, cmd->argv[i]);
		else
			append_word_envp(data, cmd->argv[i]);
		i++;
		if (data->error)
			return ;
	}
}

void	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd -> argv[i])
		i++;
	if (i == 1)
		sort_and_print(data, cmd);
	else if (i > 1)
		declare_vars(data, cmd);
}
