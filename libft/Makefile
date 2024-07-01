# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 21:50:08 by jwadie-a          #+#    #+#              #
#    Updated: 2024/02/14 20:10:48 by jwadie-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS += -Wall -Wextra -Werror
NAME= libft.a
SRC= ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_isspace.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_split2.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	free_2d.c\
	get_next_line.c\
	get_next_line_utils.c\
	ft_printf.c\
	ft_parse.c\
	ft_printf_putnbr.c\
	ft_printf_putstr.c
	
OBJ= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
#	$(CC) $(CFLAGS) -c $(SRC) 
	ar -crs libft.a $(OBJ)

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re : fclean all

