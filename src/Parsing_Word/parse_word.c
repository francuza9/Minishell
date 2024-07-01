/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:56:34 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/09 06:59:03 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_word(t_data *data, t_cmd *cmd, t_word *word)
{
	if (data->error)
		return ;
	if (word->type == T_HEREDOC_LIM)
		parse_heredoc_lim(data, cmd, word);
	else if (cmd->err_msg)
		return ;
	else if (word->type == T_ARGV)
		parse_argv(data, cmd, word->word);
	else
		parse_redirections(data, cmd, word);
}

void	parse_heredoc_lim(t_data *data, t_cmd *cmd, t_word *word)
{
	char	*buffer;
	char	**temp;

	if (ft_strchr(word->word, '\'') || ft_strchr(word->word, '"'))
		cmd->here_doc_vars = false;
	else
		cmd->here_doc_vars = true;
	temp = ft_split2(word->word, false);
	if (!temp)
	{
		data->error = MALLOC_ERR;
		return ;
	}
	buffer = temp[0];
	free(temp);
	if (!buffer)
		buffer = ft_strdup("");
	if (!append_word(&cmd->redirects, buffer, word->type, word->is_fd))
		data->error = MALLOC_ERR;
}

void	parse_redirections(t_data *data, t_cmd *cmd, t_word *word)
{
	char	*s;
	char	*buffer;

	s = word->word;
	buffer = NULL;
	while (*s != '\0')
	{
		if (*s == '\'')
			s = handle_quotes(data, &buffer, s);
		else if (*s == '"')
			s = handle_dquotes(data, &buffer, s);
		else
			s = redirect_no_quotes(data, cmd, &buffer, s);
		if (s == NULL)
		{
			free (buffer);
			data->error = MALLOC_ERR;
			return ;
		}
	}
	if (!buffer || cmd->err_msg == (char *) TEMP_ERR)
		cmd->err_msg = ft_strjoin(word->word, AMB_REDIRECT);
	else if (!append_word(&cmd->redirects, buffer, word->type, word->is_fd))
		data->error = MALLOC_ERR;
}

void	parse_argv(t_data *data, t_cmd *cmd, char *word)
{
	char	*s;
	char	*buffer;

	s = word;
	buffer = NULL;
	while (*s != '\0')
	{
		if (*s == '\'')
			s = handle_quotes(data, &buffer, s);
		else if (*s == '"')
			s = handle_dquotes(data, &buffer, s);
		else
			s = handle_no_quotes(data, cmd, &buffer, s);
		if (s == NULL)
		{
			free(buffer);
			data->error = MALLOC_ERR;
			return ;
		}
	}
	if (buffer)
		buffer = add_to_argv(data, cmd, buffer, ft_strlen(buffer));
	free(buffer);
}

char	*handle_env_var(t_data *data, char **buffer, char *s)
{
	int	i;

	if (*(s + 1) == '?')
	{
		*buffer = append_exit_status(data, *buffer);
		return (s + 2);
	}
	if (ft_isdigit((int) *(s + 1)))
	{
		*buffer = append_var_value(data, *buffer, s, 2);
		return (s + 2);
	}
	i = 1;
	while (check_var_char(s[i]))
		i++;
	*buffer = append_var_value(data, *buffer, s, i);
	return (s + i);
}
