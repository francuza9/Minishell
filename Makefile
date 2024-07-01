NAME	=	minishell

CC	=	cc
CFLAGS	=	-g -Wall -Werror -Wextra

FLAGS 	=	-lreadline

LIBFT	=	cd libft && make
LIB	=	libft/libft.a

CMD	=	src/Commands/
PE	=	src/Parsing_Errors/
PW	=	src/Parsing_Word/
P	=	src/Parsing/
EX	=	src/EXECUTION/
O	=	src/Others/

SRCS	=	$(O)utils.c \
			$(O)main.c \
			$(O)main_utils.c \
			$(O)signals.c \
			$(O)cleanup.c \
			$(CMD)pwd.c \
			$(CMD)cd.c \
			$(CMD)env.c \
			$(CMD)echo.c \
			$(CMD)commands_utils.c \
			$(CMD)unset.c \
			$(CMD)exit.c \
			$(CMD)export.c \
			$(CMD)export_declares.c \
			$(CMD)export_prints.c \
			$(CMD)export_errs.c \
			$(PW)append_to_buffer.c \
			$(PW)find_env_value.c \
			$(PW)parse_word.c \
			$(PW)handle_quotes.c \
			$(PW)parse_word_utils.c \
			$(PW)cmd_array_utils.c \
			$(PE)parsing_errors_utils.c \
			$(PE)parsing_errors.c \
			$(P)parsing_groups.c \
			$(P)parsing.c \
			$(P)node_manips.c \
			$(P)node_tools.c \
			$(P)parsing_utils.c \
			$(EX)execution.c \
			$(EX)execution_utils.c \
			$(EX)file_handling.c \
			$(EX)get_command_path.c \
			$(EX)here_doc.c \
			$(EX)heredoc_utils.c \
			$(EX)create_temp_file.c \
			$(EX)exec_single_cmd.c \
			$(EX)exec_piped_cmds.c

OBJS	=	$(SRCS:.c=.o)


all	: $(NAME)

$(NAME) : comp_start ft_minishell

comp_start:
	@$(LIBFT)

ft_minishell: $(OBJS)
	@$(CC) $(CFLAGS) $(FLAGS) $(OBJS) $(LIB) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@cd libft && make clean

fclean: clean
	@rm -rf $(NAME)
	@cd libft && make fclean

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

re:	fclean all

.PHONY : all clean fclean re libft
