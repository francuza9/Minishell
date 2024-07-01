/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadie-a <jwadie-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:11:40 by jwadie-a          #+#    #+#             */
/*   Updated: 2024/03/09 20:57:07 by jwadie-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>

//Libft
# include "./libft/libft.h"

# define TEMP_ERR		0x01

# define SPACES			"\f\t\v\n\r "

# define T_ARGV			1
# define T_INFILE		2
# define T_OUTFILE_TR	3
# define T_OUTFILE_AP	4
# define T_HEREDOC_LIM	5

# define N_ENOUGH_FDS	"Max amount of fds exceeded. Aborting\n"
# define MALLOC_MSG		"Memory allocation failed. Terminating program\n"
# define NO_SUCH_FILE	": No such file or directory\n"
# define HERE_WARNING	"here-document delimited by end-of-file (wanted '"
# define AMB_REDIRECT	": ambiguous redirect\n"
# define CMD_NOT_FOUND	": command not found\n"
# define PERM_DENIED	": Permission denied\n"
# define IS_A_DIR_MSG	": Is a directory\n"

# define NO_ERROR		0
# define MALLOC_ERR		3
# define NO_FD_ERR		2
# define AMB_RDRCT_ERR	1
# define FILE_ERROR		1
# define INVD_OPTN_ERR	2
# define ENV_INV_OPT_ER	125
# define IS_A_DIR_ERR	126
# define PERM_DNIED_ERR	126
# define NO_SUCH_F_ERR	127
# define CMD_NFND_ERR	127
# define CORE_DUMPED	131
# define INTRPT_CODE	130

# define LONG_INT_MAX	"9223372036854775807"
# define LONG_INT_MIN	"-9223372036854775808"

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;

typedef struct s_word
{
	int				is_fd;
	char			*word;
	int				type;
	struct s_word	*next;
}	t_word;

typedef struct s_cmd
{
	t_word			*redirects;
	char			**argv;
	char			*path;
	char			*err_msg;
	bool			here_doc_vars;
	int				saved_fd_in;
	int				saved_fd_out;
	int				exit_status;
	int				*temp_i;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char		*path;
	char		*line;
	t_cmd		*commands;
	t_node		*temp_files;
	char		**envp;
	char		**groups;
	int			pipe_count;
	int			pipe1[2];
	int			pipe2[2];
	int			saved_stdin;
	int			saved_stderr;
	bool		is_exit;
	int			exit_status;
	int			new_exit_status;
	int			error;
}	t_data;

//EXECUTION
int		exec_start(t_data *data);
int		exec_single_command(t_data *data);
int		exec_piped_commands(t_data *data, t_cmd *commands);

bool	is_builtin(char *command);
int		get_fds(t_data *data, t_cmd *command);
int		get_command_path(t_data *data, t_cmd *cmd);
void	handle_piping(t_data *data, t_cmd *cmd);
int		wait_last_child(pid_t pid);

void	collect_heredocs(t_data *data);
int		create_temp_file(t_data *data, int *fd_write);
char	*heredoc_env_vars(t_data *data, char *temp);
void	print_heredoc_warning(char *limiter);
void	close_heredoc_fds(t_data *data, t_cmd *exception_cmd);

//Commands
int		call_commands(t_data *data, t_cmd *cmd);
void	ft_exit(t_data *data, t_cmd *cmd);
void	ft_export(t_data *data, t_cmd *cmd);
int		ft_pwd(t_data *data, t_cmd *cmd);
int		ft_cd(t_data *data, t_cmd *cmd);
int		ft_env(t_data *data, t_cmd *cmd);
int		ft_echo(t_data *data, t_cmd *cmd);
int		ft_unset(t_data *data, t_cmd *cmd);

//Command Utils
void	update_pwd(t_data *data);
void	unset_var(t_data *data, char *var);
void	print_nls(t_data *data, t_cmd *cmd);
void	sort_and_print(t_data *data, t_cmd *cmd);
void	append_word_envp(t_data *data, char *argv);
char	*go_path(t_data *data, char *dif_path, char *path, t_cmd *cmd);
char	**envpcpy_bigger(t_data *data, char **envp);
bool	first_bigger(t_data *data, t_cmd *cmd, int i);
bool	var_errors(t_data *data, char *argv);
bool	already_exist(t_data *data, char *argv);
bool	export_invalid(t_data *data, char *argv);
bool	export_not_valid(t_data *data, char *argv);
char	*get_real_pwd(t_data *data);
int		exit_cd(void);

//Parsing
void	set_prios(t_word *words);
void	send_words(t_data *data, t_cmd *cmd, t_word *word);
void	parse_string(t_data *data, t_cmd *cmd, char *str);
void	parse(t_data *data, char *str);
int		valid_argv(char *str, int i);
int		append_heredoc(t_word **word, char *str, int i);
int		append_doubleout(t_word **word, char *str, int i);
int		append_out(t_word **word, char *str, int i);
int		append_in(t_word **word, char *str, int i);

//Parsing Errors
void	ignore_comment(char **line);
int		skip_inside(char *str, int i);
int		initial_parsing(t_data *data);
int		check_open_quotes(char	*str);

//Parse Word
void	parse_word(t_data *data, t_cmd *cmd, t_word *word);
void	parse_env_var(t_data *data, t_cmd *cmd, char **buffer, char **s);
void	parse_argv(t_data *data, t_cmd *cmd, char *word);
void	parse_heredoc_lim(t_data *data, t_cmd *cmd, t_word *word);
void	parse_redirections(t_data *data, t_cmd *cmd, t_word *word);

char	*append_var_value(t_data *data, char *temp, char *s, int i);
char	*append_to_buffer(t_data *data, char *temp, char *s, int i);
char	*append_exit_status(t_data *data, char *temp);

char	*handle_env_var(t_data *data, char **buffer, char *s);
char	*handle_quotes(t_data *data, char **buffer, char *s);
char	*handle_dquotes(t_data *data, char **buffer, char *s);
char	*handle_no_quotes(t_data *data, t_cmd *cmd, char **buffer, char *s);
char	*redirect_no_quotes(t_data *data, t_cmd *cmd, char **buffer, char *s);

char	**handle_array(char **argv, char *str);
char	*remove_leading_spaces(char *buffer, int j);
char	*add_to_argv(t_data *data, t_cmd *cmd, char *str, int j);
int		check_spaces(char *s);
int		check_var_char(char c);

//Utils
t_word	*find_last_word(t_word *word);
t_cmd	*find_last_command(t_cmd *cmd);
t_node	*find_last_node(t_node *node);
void	signals_and_prompt(t_data *data);
void	clear_and_exit(t_data *data);
void	check_max_heredocs(t_data *data, char *str, int heredocs);
bool	append_word(t_word **word, char *str, int type, bool is_fd);
bool	append_command(t_cmd **cmd);
bool	append_node(t_node **node, char *str);
void	init_main(t_data *data, char **envp);
bool	ft_isdelimiter(char c);
bool	parse_and_execute(t_data *data);
char	**envpcpy(char **envp);
char	*line_pwd(void);
char	*find_env_value(t_data *data, char *var_name);
int		valid_filename(char *str, int i);
int		choose_redirect(t_word **word, char *str, int i);
void	handle_errors(t_data *data);

//Sig Handlers
void	sig_handler(int signum);
void	sig_handler_doc(int signum);
void	sig_handler_dump(int signum);
void	sig_handler_int(int signum);

//Cleanup
void	child_cleanup(t_data *data, int exit_status);
void	clean_and_exit(t_data *data, char *str);
void	free_temp_files(t_node **temp_files);
void	free_commands(t_cmd **commands);
void	free_words(t_word **words);

#endif