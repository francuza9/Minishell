/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:43:22 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 05:40:32 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	export_invalid(t_data *data, char *argv)
{
	write(STDERR_FILENO, argv, 2);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	data->new_exit_status = INVD_OPTN_ERR;
	return (true);
}

bool	export_not_valid(t_data *data, char *argv)
{
	write(STDERR_FILENO, argv, ft_strlen(argv));
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	data->new_exit_status = 1;
	return (true);
}
