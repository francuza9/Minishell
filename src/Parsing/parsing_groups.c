/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_groups.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:18 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 06:58:42 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	append_argv(t_word **word, char *str, int i)
{
	char	*temp;
	int		j;

	j = i;
	i = valid_argv(str, i);
	temp = ft_substr(str, j, i - j);
	if (!temp || !append_word(word, temp, T_ARGV, false))
		return (-2);
	i--;
	return (i);
}

void	for_outs(t_word *words, int i)
{
	while (i)
	{
		if (words->type == T_OUTFILE_AP || words->type == T_OUTFILE_TR)
			i--;
		if (!i && (words->type == T_OUTFILE_AP || words->type == T_OUTFILE_TR))
			words->is_fd = true;
		words = words -> next;
	}
}

void	for_ins(t_word *words, int i)
{
	while (i)
	{
		if (words->type == T_INFILE || words->type == T_HEREDOC_LIM)
			i--;
		if (!i && (words->type == T_INFILE || words->type == T_HEREDOC_LIM))
			words->is_fd = true;
		words = words -> next;
	}
}

void	set_prios(t_word *words)
{
	t_word	*ptr;
	int		in_count;
	int		out_count;

	ptr = words;
	in_count = 0;
	out_count = 0;
	while (ptr)
	{
		if (ptr->type == T_INFILE || ptr->type == T_HEREDOC_LIM)
			in_count++;
		else if (ptr->type == T_OUTFILE_TR || ptr->type == T_OUTFILE_AP)
			out_count++;
		ptr = ptr -> next;
	}
	ptr = words;
	for_ins(ptr, in_count);
	for_outs(ptr, out_count);
}

void	parse_string(t_data *data, t_cmd *cmd, char *str)
{
	t_word	*word;
	int		i;

	word = NULL;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') \
		|| (str[i] == '>' && str[i + 1] == '>') \
		|| str[i] == '>' || str[i] == '<')
			i = choose_redirect(&word, str, i);
		else
		{
			if (!ft_isdelimiter(str[i]))
				i = append_argv(&word, str, i);
			i++;
		}
		if (i < 0)
		{
			free_words(&word);
			clean_and_exit(data, MALLOC_MSG);
		}
	}
	send_words(data, cmd, word);
}
