/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:16:49 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/24 00:34:21 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <limits.h>
# include <termios.h>
# include "../sources/shell_utils/libft/libft.h"

# ifndef RET_NOT_FOUND_VALUE
#  define RET_NOT_FOUND_VALUE 127
# endif

# ifndef RET_SYNTAX_ERROR
#  define RET_SYNTAX_ERROR 258
# endif

# ifndef MAX_PIPES_ALLOWED
#  define MAX_PIPES_ALLOWED 500
# endif

# ifndef RET_NOT_EXEC_VALUE
#  define RET_NOT_EXEC_VALUE 126
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define RET_LAST_EXIT_NUM 1111
# define GREEN "\033[92m"
# define RESET "\033[00m"
# define MSG_E_M "minishell: memory allocation failed\n"
# define MSG_E_ "minishell: pipe creation failed\n"
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"
# define EXIT_SUCCESS 0
# define EXIT_FAIL_MALLOC 1
# define EXIT_FAIL_PIPE 2
# define EXIT_FAIL_FORK 3
# define EXIT_FAIL_EXEC 4
# define EXIT_SYNTAX_ERROR 5
# define SUCCESS 0
# define FAILURE 1

enum			e_token_type
{
	SPACE_ = 1,
	ARG,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END,
	CRR_QTS,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};
typedef struct s_malloc
{
	void				*ptr;
	struct s_malloc		*next;
}	t_malloc;

typedef struct s_redirect
{
	char	*in_file_name;
	char	*out_file_name;
	char	*break_delimiter;
	bool	has_quotes;
	int		fd_in;
	int		fd_out;
	int		fd_stdin_backup;
	int		fd_stdout_backup;
}				t_redirect;

typedef struct s_command
{
	char				*cmd_name;
	char				*cmd_path;
	char				**arguments;
	bool				has_pipe;
	int					*pipe_fds;
	t_redirect			*_io_redirect;
	struct s_command	*next;
	struct s_command	*previous;
}				t_command;

typedef struct s_token
{
	char			*token_content;
	int				token_type;
	char			*original_content;
	bool			env_var_exist;
	int				token_status;
	bool			should_concatenate;
	struct s_token	*previous;
	struct s_token	*next;
}				t_token;

typedef struct s_shell_data
{
	char		*line_input;
	char		**env__;
	char		*current_dir;
	char		*old_dir;
	int			exit_status;
	t_token		*token;
	t_command	*cmd;
	pid_t		pid;
}				t_shell_data;

t_command	*lst_new_cmd(bool value);
char		*replace_remove_value_v_token(t_token **token_node, char *content,
				char *value_v, int idx);
int			remove_variable_from_token(t_token **token_node, char *content,
				int index);
int			handle_quotes_case(t_token **token_node, char *value_v,
				char *content, int index);
int			handle_no_quotes_case(t_token **token_node, char *value_v,
				char *content, int index);
int			handle_variable_split_utils(t_token **token_node,
				char **split_values, t_token *prev, t_token *next);
void		init_cmd(t_command **cmd);
t_command	*get_last_command(t_command *lst_cmd);
bool		fih_space(char *str);
int			create_echo_arguments(t_token **current_token, t_command *last_cmd);
bool		init_minimal_env(t_shell_data *data, char *cwd);
void		update_shlvl(t_shell_data *data);
bool		add_env_var(t_shell_data *data, char *new_var);
bool		init_data(t_shell_data *shell_data, char **env);
bool		check_first_arg(int ac, char **av);
int			init_check_line_input(t_shell_data *data);
int			ft_word_count(char *str, char sep);
int			tokens(t_shell_data *data, char *input_line);
int			update_quote_status(char *input_line, int current_status_quote,
				int position);
int			is_shell_separator(char *input_line, int index);
int			check_var(t_token **lst_token);
char		*get_env_var_value(char **env, char *key);
int			get_env_var_index(char **env__, char *var);
char		*get_variable_value(t_token *token, char *content,
				t_shell_data *data);
int			var_exist(t_shell_data *data, char *var);
int			env_var_count(char **env);
int			process_tokens_remove_quotes(t_shell_data *data);
void		lst_add_back_token(t_token **lst_token, t_token *new_node_token);
t_token		*lst_new_token(char *extracted_word, char *backup, int type,
				int status_quote);
void		delete_token_chain(t_token **new_token, void (*del)(void *));
bool		if_quotes_and_correct_quotes(t_token **token_node, int i);
char		*join_strings(char *str, char *add);
int			calculate_var_name_length(char *content);
int			errmsg_cmd(char *cmd_name, char *error_detail,
				char *error_text, int error_code);
void		display_error(char *error_msg_type,
				char *specifics, int use_quotes);
bool		is_separator_char(char c);
int			signals(int old_exit_status);
void		update_status(t_token **token_node, char c);
bool		creat_commands(t_shell_data *data, t_token *token);
void		delete_token_node(t_token *node, void (*del)(void *));
void		clean_empty_var_args(t_token **token_list);
int			append_next_echo_argument(t_token **current_token, t_command *cmd);
void		ensure_args_array(t_shell_data *data);
void		init_redir_struct(t_command *cmd);
void		handle_input(t_command **last_cmd, t_token **list_token);
void		handle_trunc(t_command **cmd, t_token **list_token);
void		handle_append(t_command **cmd, t_token **list_token);
void		handle_pipe(t_command **cmd, t_token **list_token);
bool		handle_heredoc(t_shell_data *data, t_token **token,
				t_command **cmd);
void		start_minishell(t_shell_data *data);
void		safe_free(void *ptr);
void		free_string_array(char **string_array);
void		free_shell_data(t_shell_data *data, bool clear_history);
int			shell_execution(t_shell_data *data);
void		terminate_shell(t_shell_data *data, int exit_code);
int			execute_builtin_command(t_shell_data *data, t_command *cmd);
int			shell_execute_command(t_shell_data *data, t_command *cmd);
int			pwd_builtin_cmd(t_shell_data *data, char **args);
int			echo_builtin_cmd(char **args);
int			env_builtin_cmd(t_shell_data *data, char **args);
int			cd_builtin_cmd(t_shell_data *data, char **args);
int			export_builtin_cmd(t_shell_data *data, char **args);
int			unset_builtin_cmd(t_shell_data *data, char **args);
int			exit_builtin_cmd(t_shell_data *data, char **args);
bool		update_set_env_var(t_shell_data *data,
				char *key_var, char *var_val);
bool		create_pipe(t_shell_data *data);
bool		set_pipe(t_command *cmds, t_command *cmd);
void		close_pipe(t_command *commands, t_command *ignore_cmd);
bool		check_infile_outfile(t_redirect *io);
bool		apply_redirection(t_redirect *in_out);
bool		reset_redirection(t_redirect *in_out);
void		close_fds(t_command *commands, bool close_backup);
int			check_cmd_if_exist(t_shell_data *data, t_command *cmd);
bool		check_cmd_isdir(char *command);
void		lst_add_back_cmd(t_command **lst_cmd, t_command *new_node_cmd);
bool		is_valid_env_var_key(char *var);
void		heredoc_signals(void);
void		heredoc_cleanup(t_shell_data *data);
bool		remove_old_file_ref(t_redirect *io, bool infile);
bool		fill_heredoc(t_shell_data *data, t_redirect *io,
				int fd, int *delims_left);
char		*erase_and_replace(t_token **token_node, char *str, char *var_value,
				int index);
char		*replace_str_heredoc(char *str, char *var_value, int index);
void		copy_var_value(char *new_str, char *value_v, int *new_index);
int			count_argument_tokens(t_token *current_token);
char		*concat_vars(t_token **token_courant);
int			creat_command_arguments(t_token **current_token, t_command *cmd);
int			append_next_command_argument(t_token **token_node,
				t_command *last_cmd);
char		*get_new_token_string(char *content, char *value_v,
				int new_str_length, int index);
char		*get_cmd_path(t_shell_data *data, char *name);
char		**realloc_env(t_shell_data *data, int size);
void		update_env_path(t_shell_data *data, char *cur_dir);
void		reset_terminal_settings(void);
char		*search_value_env(t_shell_data *data, char *variable_name);
bool		is_valid_var_char(char c);
int			check_env_and_syntax_errors(t_token **lst_token);
char		*identify_var(char *content);
int			save_token_separator(char *input_line, t_token **lst_token,
				int index, int token_type);
int			replace_var_with_value_in_token(t_token **token_node, char *value_v,
				int index, int inside_quotes);
bool		check_line_limit_of_delimiters(char *heredoc_line);
int			get_status_exit_in_sig(int val);
void		get_status_heredoc_sigint_delimters(int v);
char		*get_other_path(t_shell_data *data, char *path);
char		*get_dotdot_path(t_shell_data *data);
bool		can_access_dir(const char *path);
int			get_exit_code(char *arg, bool *error, int exit_status);
long		ft_atoi_long(const char *str, bool *error);
bool		check_out_of_range(int neg, unsigned long long num, bool *error);
char		*handle_getcwd_failure(t_shell_data *data, char *path);
bool		handle_cd_dotdot_case(t_shell_data *data, char *path);
bool		validate_cmd_and_files(t_shell_data *data, t_command *cmd);
int			initialize_execution(t_shell_data *data);
bool		is_builtin(char *cmd_name);
void		close_previous_pipe(t_command *cmd);
char		*get_delimiter(char *delim, bool *quotes);
char		*get_heredoc_name(void);
bool		heredoc_res(t_redirect *io, int result);
char		*var_expander_heredoc(t_shell_data *data, char *str);
void		lst_delone_cmd(t_command *lst, void (*del)(void *));
void		lst_clear_cmd(t_command **lst, void (*del)(void *));
bool		contains_quotes(char *str);
void		update_token_status_on_quote(t_token **token_node, int *i);
void		free_io(t_redirect *io);
int			expand_env_vars(t_shell_data *data, t_token **lst_token);
bool		is_char_between_double_quotes(char *content, int i);
void		process_command_name(t_token **tmp, t_command *last_cmd);
bool		should_set_command_name(t_token *tmp, t_command *last_cmd);
void		split_and_fill_command_args(t_command *last_cmd, char *cmd_str);
int			append_command_arguments(t_token **current_token,
				t_command *command);
char		**copy_tokens_into_args(int len, char **args_new,
				t_command *last_cmd, t_token **token_node);
int			count_simple_tokens(t_token *tmp);
void		*ft_malloc(size_t size);
void		free_malloc_list(int status);
#endif
