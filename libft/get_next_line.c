/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:06:19 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/01/14 16:51:23 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*stash_fd[1024];
	t_gnl_list			**stash;
	char				*next_line;
	int					len;
	int					len_cpy;

	stash = &stash_fd[fd];
	*stash = add_to_stash(stash, fd);
	if (*stash == NULL)
		return (NULL);
	next_line = collect_line_from_stash(*stash);
	if (next_line == NULL || !check_for_newline(*stash))
	{
		clear_gnl_list(stash, TRUE);
		return (next_line);
	}
	clear_gnl_list(stash, FALSE);
	len = check_for_newline(*stash);
	len_cpy = ft_strlen((*stash)->content) - check_for_newline(*stash) + 1;
	ft_copycat((*stash)->content, (*stash)->content + len, len_cpy, FALSE);
	if ((*stash)->content[0] == '\0')
		clear_gnl_list(stash, TRUE);
	return (next_line);
}

char	*collect_line_from_stash(t_gnl_list *stash)
{
	char		*next_line;
	t_gnl_list	*node;
	size_t		length;

	length = 0;
	if (!check_for_newline(stash))
		next_line = malloc(lst_strlen(stash) + 1);
	else
		next_line = malloc(check_for_newline(stash) + 1);
	if (next_line == NULL)
		return (NULL);
	next_line[0] = '\0';
	node = stash;
	while (node->next != NULL)
	{
		length = ft_strlen(node->content);
		ft_copycat(next_line, node->content, length + 1, TRUE);
		node = node->next;
	}
	if (!check_for_newline(node))
		length = ft_strlen(node->content);
	else
		length = check_for_newline(node);
	ft_copycat(next_line, node->content, length + 1, TRUE);
	return (next_line);
}

t_gnl_list	*add_to_stash(t_gnl_list **stash, int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (!check_for_newline(*stash))
	{
		bytes_read = read(fd, (void *)buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && !(*stash)))
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		*stash = append_to_gnl_list(*stash, buffer);
		if (*stash == NULL || (bytes_read < BUFFER_SIZE))
			break ;
	}
	free(buffer);
	return (*stash);
}

int	lst_strlen(t_gnl_list *lst)
{
	int	len;
	int	i;

	if (lst == NULL)
		return (0);
	len = 0;
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

int	check_for_newline(t_gnl_list *stash)
{
	t_gnl_list	*node;
	int			count;
	int			i;

	if (stash == NULL)
		return (0);
	node = stash;
	count = 0;
	while (node != NULL)
	{
		i = 0;
		while (node->content[i] != '\0')
		{
			if (node->content[i] == '\n')
				return (count + 1);
			i++;
			count++;
		}
		node = node->next;
	}
	return (0);
}
