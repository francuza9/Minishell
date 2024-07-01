/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:37:07 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/09 06:58:57 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*add_to_argv(t_data *data, t_cmd *cmd, char *str, int j)
{
	char	*sub;
	char	*new;
	char	**new_argv;

	sub = ft_substr(str, 0, j);
	if (!sub)
		data->error = MALLOC_ERR;
	new_argv = handle_array(cmd->argv, sub);
	if (!new_argv)
	{
		data->error = MALLOC_ERR;
		free(sub);
		free(str);
		return (NULL);
	}
	free(cmd->argv);
	cmd->argv = new_argv;
	while (ft_isspace(str[j]))
		j++;
	new = ft_substr(str, j, ft_strlen(str) - j + 1);
	free(str);
	if (!new)
		data->error = MALLOC_ERR;
	return (new);
}

char	**handle_array(char **argv, char *str)
{
	int		i;
	char	**arr;

	i = 0;
	if (!argv)
		arr = malloc(sizeof(char *) * 2);
	else
	{
		while (argv[i])
			i++;
		arr = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (argv[i])
		{
			if (arr)
				arr[i] = argv[i];
			i++;
		}
	}
	if (arr)
		arr[i] = str;
	if (arr)
		arr[i + 1] = NULL;
	return (arr);
}
