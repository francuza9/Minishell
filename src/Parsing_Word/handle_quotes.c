/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 23:32:00 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/06 02:47:11 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_quotes(t_data *data, char **buffer, char *s)
{
	int	i;

	s++;
	i = 0;
	while (s[i] != '\'' && s[i] != '\0')
		i++;
	if (!(*buffer))
		*buffer = ft_strdup("");
	if (!(*buffer))
		return (NULL);
	*buffer = append_to_buffer(data, *buffer, s, i);
	if (!(*buffer))
		return (NULL);
	return (s + i + (s[i] != '\0'));
}

char	*handle_dquotes(t_data *data, char **buffer, char *s)
{
	int	i;

	s++;
	i = 0;
	while (s[i] != '"' && s[i] != '\0')
	{
		if (s[i] == '$')
		{
			*buffer = append_to_buffer(data, *buffer, s, i);
			s = handle_env_var(data, buffer, s + i);
			i = 0;
		}
		else
			i++;
	}
	if (!(*buffer))
		*buffer = ft_strdup("");
	*buffer = append_to_buffer(data, *buffer, s, i);
	return (s + i + (s[i] != '\0'));
}

char	*handle_no_quotes(t_data *data, t_cmd *cmd, char **buffer, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '"' && s[i] != '\'' && s[i] != '\0')
	{
		if (s[i] == '$')
		{
			parse_env_var(data, cmd, buffer, &s);
			i = 0;
		}
		else
			i++;
	}
	*buffer = append_to_buffer(data, *buffer, s, i);
	if (*buffer && !(*buffer)[0])
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (s + i);
}

char	*redirect_no_quotes(t_data *data, t_cmd *cmd, char **buffer, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != '"' && s[i] != '\'' && s[i] != '\0')
	{
		if (s[i] == '$')
		{
			*buffer = append_to_buffer(data, *buffer, s, i);
			if (*buffer)
				j = ft_strlen(*buffer);
			else
				j = 0;
			s = handle_env_var(data, buffer, s + i);
			if (*buffer && check_spaces(*buffer + j))
				cmd->err_msg = (char *) TEMP_ERR;
			i = 0;
		}
		else
			i++;
	}
	*buffer = append_to_buffer(data, *buffer, s, i);
	return (s + i);
}

void	parse_env_var(t_data *data, t_cmd *cmd, char **buffer, char **s)
{
	int	i;
	int	j;

	i = (int)(ft_strchr(*s, '$') - *s);
	*buffer = append_to_buffer(data, *buffer, *s, i);
	if (*buffer)
		j = ft_strlen(*buffer);
	else
		j = 0;
	*s = handle_env_var(data, buffer, *s + i);
	if (!(*buffer))
		return ;
	if (ft_isspace((*buffer)[j]))
		*buffer = remove_leading_spaces(*buffer, j);
	while ((*buffer) && (*buffer)[j] != '\0')
	{
		if (ft_isspace((int)(*buffer)[j]))
		{
			*buffer = add_to_argv(data, cmd, *buffer, j);
			j = 0;
		}
		else
			j++;
	}
}
