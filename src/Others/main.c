/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:10:54 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/07 23:22:08 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	g_flag = false;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1 && argv)
		exit (EXIT_FAILURE);
	init_main(&data, envp);
	while (1)
	{
		if (data.is_exit == true)
			clear_and_exit(&data);
		signals_and_prompt(&data);
		if (*data.line && parse_and_execute(&data))
			continue ;
		free(data.path);
		data.path = NULL;
		free(data.line);
		data.line = NULL;
	}
	return (0);
}
