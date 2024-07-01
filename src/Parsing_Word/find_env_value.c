/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:00:53 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/07 01:33:09 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_env_value(t_data *data, char *var_name)
{
	int		i;
	char	*var_value;

	if (!var_name)
		return (NULL);
	var_value = NULL;
	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp(var_name, data->envp[i], ft_strlen(var_name)) \
		&& data->envp[i][ft_strlen(var_name)] == '=')
		{
			var_value = ft_substr(data->envp[i], ft_strlen(var_name) + 1, \
			ft_strlen(data->envp[i]) - ft_strlen(var_name) - 1);
			if (!var_value)
				data->error = MALLOC_ERR;
			break ;
		}
	}
	if (var_value && !var_value[0])
	{
		free(var_value);
		return (NULL);
	}
	return (var_value);
}
