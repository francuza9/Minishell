/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_manips.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:16 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/07 01:45:00 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_command(t_cmd *cmd)
{
	cmd->redirects = NULL;
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->err_msg = NULL;
	cmd->here_doc_vars = false;
	cmd->saved_fd_in = STDIN_FILENO;
	cmd->saved_fd_out = STDOUT_FILENO;
	cmd->next = NULL;
}

bool	append_command(t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*last;

	new = malloc (sizeof(t_cmd));
	if (!new)
		return (false);
	init_command(new);
	if (!(*cmd))
		*cmd = new;
	else
	{
		last = find_last_command(*cmd);
		last -> next = new;
	}
	return (true);
}

bool	append_word(t_word **word, char *str, int type, bool is_fd)
{
	t_word	*new;
	t_word	*last;

	new = malloc (sizeof(t_word));
	if (!new)
	{
		free(str);
		return (false);
	}
	new->word = str;
	new->type = type;
	new->next = NULL;
	new->is_fd = is_fd;
	if (!(*word))
		*word = new;
	else
	{
		last = find_last_word(*word);
		last -> next = new;
	}
	return (true);
}

bool	append_node(t_node **node, char *str)
{
	t_node	*new;
	t_node	*last;

	new = malloc (sizeof(t_node));
	if (!new)
	{
		free(str);
		return (false);
	}
	new->str = str;
	new->next = NULL;
	if (!(*node))
		*node = new;
	else
	{
		last = find_last_node(*node);
		last -> next = new;
	}
	return (true);
}

t_node	*find_last_node(t_node *node)
{
	if (!node)
		return (NULL);
	while (node -> next)
		node = node -> next;
	return (node);
}
