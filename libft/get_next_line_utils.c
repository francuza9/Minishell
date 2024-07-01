/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:07:36 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/12/13 21:42:25 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*append_to_gnl_list(t_gnl_list *lst, char *str)
{
	t_gnl_list	*last;
	t_gnl_list	*new;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(t_gnl_list));
	if (new == NULL)
		return (NULL);
	new->content = malloc(ft_strlen(str) + 1);
	if (new->content == NULL)
		return (NULL);
	ft_copycat(new->content, str, ft_strlen(str) + 1, FALSE);
	new->next = NULL;
	last = lst_gnl_get_last(lst);
	if (last == NULL)
		lst = new;
	else
		last->next = new;
	return (lst);
}

t_gnl_list	*lst_gnl_get_last(t_gnl_list *lst)
{
	t_gnl_list	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	clear_gnl_list(t_gnl_list **lst, int clear_last)
{
	t_gnl_list	*current_node;
	t_gnl_list	*next_node;

	if (*lst == NULL)
		return ;
	current_node = *lst;
	while (current_node->next != NULL)
	{
		next_node = current_node->next;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	if (clear_last == TRUE)
	{
		free(current_node->content);
		free(current_node);
		*lst = NULL;
	}
	else
		*lst = current_node;
}

void	ft_copycat(char *dst, const char *src, size_t size, int cat)
{
	char		*end;

	if (dst == NULL || src == NULL)
		return ;
	if (cat == TRUE)
		dst += ft_strlen(dst);
	end = dst + size;
	while (dst < end && *src != '\0')
		*dst++ = *src++;
	if (dst < end)
		*dst = '\0';
	else if (size > 0)
		dst[-1] = '\0';
}
