/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:50 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 05:42:30 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	unset_err(t_cmd *cmd)
{
	bool	flag;

	flag = false;
	if (ft_strlen(cmd->argv[1]) > 1 && cmd->argv[1][0] == '-')
	{
		if (ft_strlen(cmd->argv[1]) > 2)
			flag = true;
		else if (cmd->argv[1][1] != '-')
			flag = true;
	}
	if (flag)
	{
		write(STDERR_FILENO, cmd->argv[1], 2);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	}
	return (flag);
}

void	unset_var(t_data *data, char *var)
{
	int	j;

	j = 0;
	while ((data -> envp[j]) && (ft_strncmp(data -> envp[j], \
	var, ft_strlen(var)) || ((data -> envp[j][ft_strlen(var)] != '=') \
	&& (data -> envp[j][ft_strlen(var)] != '\0'))))
		j++;
	free(data->envp[j]);
	while (data -> envp[j])
	{
		data->envp[j] = data -> envp[j + 1];
		j++;
	}
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd -> argv[i])
		i++;
	if (i < 2)
		return (0);
	if (unset_err(cmd))
		return (INVD_OPTN_ERR);
	i = 1;
	while (cmd->argv[i])
	{
		unset_var(data, cmd->argv[i]);
		i++;
	}
	return (0);
}
