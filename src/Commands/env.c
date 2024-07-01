/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:30 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 20:57:34 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	env_err(t_data *data, t_cmd *cmd)
{
	if (cmd->argv[1][0] == '-')
	{
		ft_putstr_fd("invalid option\n", 2);
		data->new_exit_status = ENV_INV_OPT_ER;
		return (true);
	}
	ft_putstr_fd(" invalid argument\n", 2);
	data->new_exit_status = NO_SUCH_F_ERR;
	return (true);
}

int	ft_env(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd -> argv[i])
		i++;
	if (i > 1 && env_err(data, cmd))
		return (data->new_exit_status);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strchr(data->envp[i], '='))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(data->envp[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
