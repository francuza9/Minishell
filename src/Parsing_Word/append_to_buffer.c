/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:43:31 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/07 01:33:09 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*append_var_value(t_data *data, char *buffer, char *s, int i)
{
	char	*new;
	char	*value;
	char	*sub;

	sub = ft_substr(s, 1, i - 1);
	value = find_env_value(data, sub);
	if (!value && i != 1)
	{
		free(sub);
		return (buffer);
	}
	if (!buffer)
		buffer = ft_strdup("");
	if (i == 1)
		new = ft_strjoin(buffer, "$");
	else
		new = ft_strjoin(buffer, value);
	free(value);
	free(buffer);
	free(sub);
	if (!new)
		data->error = MALLOC_ERR;
	return (new);
}

char	*append_to_buffer(t_data *data, char *buffer, char *s, int i)
{
	char	*new;
	char	*sub;

	if (!i || !s)
		return (buffer);
	sub = NULL;
	if (!buffer)
		buffer = ft_strdup("");
	sub = ft_substr(s, 0, i);
	new = ft_strjoin(buffer, sub);
	if (!new)
		data->error = MALLOC_ERR;
	free(buffer);
	free(sub);
	return (new);
}

char	*append_exit_status(t_data *data, char *buffer)
{
	char	*new;
	char	*alpha;

	alpha = ft_itoa(data->exit_status);
	if (!buffer)
		buffer = ft_strdup("");
	new = ft_strjoin(buffer, alpha);
	free(buffer);
	free(alpha);
	if (!new)
		data->error = MALLOC_ERR;
	return (new);
}
