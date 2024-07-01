/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:43 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 05:40:24 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_pwd(char *buffer)
{
	ft_putstr_fd(buffer, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
}

int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*buffer;
	int		i;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (i > 1 && ft_strlen(cmd->argv[1]) > 1 && cmd->argv[1][0] == '-' && \
	(ft_strlen(cmd->argv[1]) > 2 || cmd->argv[1][1] != '-'))
	{
		write(STDERR_FILENO, cmd->argv[1], 2);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		return (INVD_OPTN_ERR);
	}
	buffer = get_real_pwd(data);
	print_pwd(buffer);
	return (0);
}
