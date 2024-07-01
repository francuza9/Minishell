/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:37:37 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 22:50:57 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern bool	g_flag;

void	sig_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		g_flag = true;
		ft_putchar_fd('\n', 1);
	}
}

void	sig_handler_dump(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd(" core dumped\n", 2);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_flag = true;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_doc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_flag = true;
		close(STDERR_FILENO);
		close(STDIN_FILENO);
	}
}
