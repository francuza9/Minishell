/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:50:11 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/07 23:31:42 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*find_last_command(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	while (cmd -> next)
		cmd = cmd -> next;
	return (cmd);
}

t_word	*find_last_word(t_word *word)
{
	if (!word)
		return (0);
	while (word -> next)
		word = word -> next;
	return (word);
}

int	choose_redirect(t_word **word, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		i = append_heredoc(word, str, i);
	else if (str[i] == '>' && str[i + 1] == '>')
		i = append_doubleout(word, str, i);
	else if (str[i] == '>')
		i = append_out(word, str, i);
	else if (str[i] == '<')
		i = append_in(word, str, i);
	return (i);
}
