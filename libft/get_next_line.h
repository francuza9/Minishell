/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:06:56 by jwadie-a          #+#    #+#             */
/*   Updated: 2023/12/13 21:40:30 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define TRUE	1
# define FALSE	0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

typedef struct s_gnl_list
{
	char				*content;
	struct s_gnl_list	*next;
}	t_gnl_list;

char		*get_next_line(int fd);
char		*collect_line_from_stash(t_gnl_list *stash);
t_gnl_list	*add_to_stash(t_gnl_list **stash, int fd);
int			check_for_newline(t_gnl_list *stash);
int			lst_strlen(t_gnl_list *lst);
t_gnl_list	*append_to_gnl_list(t_gnl_list *lst, char *str);
t_gnl_list	*lst_gnl_get_last(t_gnl_list *lst);
void		clear_gnl_list(t_gnl_list **lst, int clear_last);
void		ft_copycat(char *dst, const char *src, size_t size, int cat);

#endif
