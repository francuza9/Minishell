/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtskitis <gtskitis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:11:19 by gtskitis          #+#    #+#             */
/*   Updated: 2024/03/06 00:50:33 by gtskitis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	append_out(t_word **word, char *str, int i)
{
	char	*temp;
	int		j;

	i += 1;
	while (ft_isspace(str[i]))
		i++;
	j = i;
	i = valid_filename(str, i);
	temp = ft_substr(str, j, i - j);
	if (!temp || !append_word(word, temp, T_OUTFILE_TR, false))
		return (-1);
	return (i);
}

int	append_in(t_word **word, char *str, int i)
{
	char	*temp;
	int		j;

	i += 1;
	while (ft_isspace(str[i]))
		i++;
	j = i;
	i = valid_filename(str, i);
	temp = ft_substr(str, j, i - j);
	if (!temp || !append_word(word, temp, T_INFILE, false))
		return (-1);
	return (i);
}

int	valid_argv(char *str, int i)
{
	int	j;

	j = i;
	while (!ft_isdelimiter(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_inside(str, i);
		i++;
	}
	if (j == i)
		return (-1);
	return (i);
}

int	append_heredoc(t_word **word, char *str, int i)
{
	char	*temp;
	int		j;

	i += 2;
	while (ft_isspace(str[i]))
		i++;
	j = i;
	i = valid_filename(str, i);
	temp = ft_substr(str, j, i - j);
	if (!temp || !append_word(word, temp, T_HEREDOC_LIM, false))
		return (-1);
	return (i);
}

int	append_doubleout(t_word **word, char *str, int i)
{
	char	*temp;
	int		j;

	i += 2;
	while (ft_isspace(str[i]))
		i++;
	j = i;
	i = valid_filename(str, i);
	temp = ft_substr(str, j, i - j);
	if (!temp || !append_word(word, temp, T_OUTFILE_AP, false))
		return (-1);
	return (i);
}
