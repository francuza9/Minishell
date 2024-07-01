/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:28 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/02 01:45:06 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	no_argv(t_cmd *cmd)
{
	if (!cmd -> argv[1])
	{
		write (STDOUT_FILENO, "\n", 1);
		return (true);
	}
	return (false);
}

void	print_args(t_cmd *cmd, int i, bool nl)
{
	int	x;

	x = i;
	while (cmd -> argv[i])
	{
		if ((i != 1 && nl == true) || (i > x && nl == false))
			write(STDOUT_FILENO, " ", 1);
		ft_putstr_fd(cmd -> argv[i], STDOUT_FILENO);
		i++;
	}
}

bool	only_ns(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	echo_start(t_data *data, t_cmd *cmd)
{
	if (no_argv(cmd))
		return (true);
	print_nls(data, cmd);
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '\0')
		write(1, "-\n", 2);
	return (false);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	bool	nl;
	int		i;

	i = 1;
	nl = true;
	if (echo_start(data, cmd))
		return (0);
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
		{
			if (only_ns(cmd->argv[i] + 1))
			{
				nl = false;
				i++;
				continue ;
			}
		}
		print_args(cmd, i, nl);
		if (nl == true)
			write(STDOUT_FILENO, "\n", 1);
		return (0);
		i++;
	}
	return (0);
}
