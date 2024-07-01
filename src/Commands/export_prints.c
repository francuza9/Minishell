/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_prints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:38 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 04:27:18 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	var_errors(t_data *data, char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[0]) && argv[0] != '_')
		return (export_not_valid(data, argv));
	while (i >= 0 && argv[i] != '=' && argv[i] != '\0')
	{
		if ((!ft_isalnum(argv[i]) && argv[i] != '_') \
		&& !(argv[i] == '+' && argv[i + 1] == '='))
			i = -2;
		i++;
	}
	if (i < 0)
		return (export_not_valid(data, argv));
	return (false);
}

bool	first_bigger(t_data *data, t_cmd *cmd, int i)
{
	int	len_first;
	int	len_second;

	len_first = 0;
	len_second = 0;
	(void)cmd;
	while ((data -> envp[i][len_first] != '=')
		&& (data -> envp[i][len_first] != '\0'))
		len_first++;
	if (data->envp[i + 1])
		while ((data -> envp[i + 1][len_second] != '=')
		&& (data -> envp[i + 1][len_second] != '\0'))
			len_second++;
	if ((len_first == len_second \
	&& (ft_strncmp(data -> envp[i], data -> envp[i + 1], len_first) < 0)) \
	|| (len_first > len_second \
	&& (ft_strncmp(data -> envp[i], data -> envp[i + 1], len_second) < 0)) \
	|| ((len_first < len_second) \
	&& (ft_strncmp(data -> envp[i], data -> envp[i + 1], len_second) < 0)))
		return (true);
	return (false);
}

bool	write_singular(t_data *data, t_cmd *cmd, bool declaration, bool equal)
{
	int	x;

	x = 0;
	while (data -> envp[*cmd->temp_i][x])
	{
		if (data -> envp[*cmd->temp_i][x] == '"' \
		|| data -> envp[*cmd->temp_i][x] == '$' \
		|| data -> envp[*cmd->temp_i][x] == '\\')
			write(STDOUT_FILENO, "\\", 1);
		ft_putchar_fd(data -> envp[*cmd->temp_i][x],
			STDOUT_FILENO);
		if ((declaration == false \
		&& data -> envp[*cmd->temp_i][x + 1] == '\0') \
		|| (data -> envp[*cmd->temp_i][x] == '=' && equal == false))
		{
			if (data -> envp[*cmd->temp_i][x + 1] == '\0' \
			&& data -> envp[*cmd->temp_i][x] == '=' && equal == false)
				write(STDOUT_FILENO, "\"", 1);
			equal = true;
			write(STDOUT_FILENO, "\"", 1);
		}
		x++;
	}
	return (equal);
}

void	declare_print(t_data *data, t_cmd *cmd)
{
	bool	equal;
	bool	declaration;
	int		i;

	i = 0;
	while (data -> envp[i])
	{
		equal = false;
		declaration = false;
		if (!ft_strchr(data -> envp[i], '='))
			declaration = true;
		if (!ft_strncmp(data->envp[i], "_=", 2))
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		cmd->temp_i = &i;
		equal = write_singular(data, cmd, declaration, equal);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	sort_and_print(t_data *data, t_cmd *cmd)
{
	char	*temp;
	int		i;
	int		j;
	int		lines;

	j = -1;
	lines = 0;
	while (data -> envp[lines])
		lines++;
	while (++j < lines)
	{
		i = 0;
		while (data -> envp[i + 1])
		{
			if (first_bigger(data, cmd, i) == false)
			{
				temp = data -> envp[i];
				data -> envp[i] = data -> envp[i + 1];
				data -> envp[i + 1] = temp;
			}
			i++;
		}
	}
	declare_print(data, cmd);
}
