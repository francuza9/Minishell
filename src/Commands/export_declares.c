/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declares.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:34 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/09 21:00:23 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_envp(t_data *data, char **new_envp, char *new_argv, int i)
{
	char	*word;

	data->envp = new_envp;
	word = malloc (sizeof(char) * ft_strlen(new_argv) + 1);
	if (!word)
	{
		data->error = MALLOC_ERR;
		free(new_argv);
		return ;
	}
	ft_strlcpy(word, new_argv, ft_strlen(new_argv) + 1);
	data->envp[i] = word;
	free(new_argv);
}

char	*skip_pos(t_data *data, char *argv, int pos)
{
	char	*temp;
	char	*temp2;
	char	*new;

	temp = ft_substr(argv, 0, pos);
	temp2 = ft_substr(argv, pos + 1, ft_strlen(argv));
	if (!temp || !temp2)
	{
		free(temp2);
		free(temp);
		data->error = MALLOC_ERR;
		return (NULL);
	}
	new = ft_strjoin(temp, temp2);
	if (!new)
		data->error = MALLOC_ERR;
	free(temp);
	free(temp2);
	return (new);
}

void	append_word_envp(t_data *data, char *argv)
{
	char	**new_envp;
	char	*new_argv;
	int		lines;
	int		i;

	lines = 0;
	while (data -> envp[lines])
		lines++;
	i = 0;
	while (argv[i] != '+' && argv[i] != '\0')
		i++;
	if (argv[i] == '+')
		new_argv = skip_pos(data, argv, i);
	else
		new_argv = ft_strdup(argv);
	if (new_argv == NULL)
		return ;
	new_envp = envpcpy_bigger(data, data->envp);
	if (!new_envp)
	{
		free(new_argv);
		return ;
	}
	handle_envp(data, new_envp, new_argv, lines);
}

char	**envpcpy_bigger(t_data *data, char **envp)
{
	char	**temp;
	int		lines;

	lines = 0;
	while (envp[lines])
		lines++;
	temp = malloc(sizeof(char *) * (lines + 2));
	if (!temp)
	{
		data->error = MALLOC_ERR;
		return (NULL);
	}
	lines = 0;
	while (envp[lines])
	{
		temp[lines] = envp[lines];
		lines++;
	}
	temp[lines] = NULL;
	temp[lines + 1] = NULL;
	free(envp);
	return (temp);
}

bool	already_exist(t_data *data, char *argv)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (argv[i] && argv[i] != '=' && argv[i] != '+')
		i++;
	temp = ft_substr(argv, 0, i);
	if (!temp)
		data->error = MALLOC_ERR;
	j = -1;
	while (data -> envp[++j])
	{
		if (temp && (!ft_strncmp(temp, data -> envp[j], i) \
		&& (data -> envp[j][i] == '=' || data -> envp[j][i] == '\0')))
		{
			free(temp);
			return (true);
		}
	}
	free(temp);
	return (false);
}
