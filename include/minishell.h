#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>

int	g_errno;

typedef struct s_token 	t_token;

typedef enum e_tokentype
{
	word,
	option,
	redirection,
	is_pipe,
	empty,
}	t_tokentype;

typedef enum e_free_options
{
	everything,
	only_tokens,
}	t_free_options;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_tokentype		type;
}				t_token;

typedef struct s_exec
{
	char			*command;
	char			**args;
	char			**input;
	char			**output;
	int				input_num;
	int				output_num;
	int				pipe_num;
	int				arg_num;
	int				output_written;
	int				input_written;

}				t_exec;

typedef struct s_data
{
	t_token			*tokens;
	t_exec			**execs;
	char			*promptline;
	char			**env;
	int				pipeflag;
	int				arg_count;
	int				exec_count;
}	t_data;

char		*prompt(t_data *data);
int			load_tokens(char **split_tokens, t_data *data);
t_tokentype	content_analyse(t_token *token);
int			parse_tokens(t_data *data);
void		put_new_promptline(void);

//Signals

void		signals(void);
void		signals_child(void);
void		handle_sigint(int sig);

//Utils
int			is_char(char place, char c);
char		*username(void);
void		free_tokens(t_data *data);
void		free_data(t_data *data);
t_data		*init_data(char **env, int args, char **argv);
void		reset_data(t_data *data);
void		free_exec(t_data *data, char *input);
char		**dupclicate_2d(char **str);
char		*ft_strjoin_s_e(char **args, int start, int end, char *c);
int			syntax(t_data *data);

//Parser
void		init_exec(t_data *data, t_token *current);
int			parse_tokens(t_data *data);
t_token		*process_token(t_data *data, t_token *current);

//Parser Utils
t_token		*write_redirection(t_data *data, t_token *current);
t_token		*write_args(t_data *data, t_token *current);
t_token		*write_output(t_data *data, t_token *current);
t_token		*write_input(t_data *data, t_token *current);
void		get_command(t_data *data);

//Parser Utils 2
int			get_exec_count(t_token	*current);
int			get_output_num(t_token *current);
int			get_input_num(t_token *current);
int			exec_has_pipe(t_token *current);
int			get_arg_num(t_token *current);

//Parser Utils 3
t_token		*write_pipe_out(t_data *data, t_token *current);
void		write_pipe_in(t_data *data);
int			is_inquotes(char *str);

//Utils Parser
int			get_exec_count(t_token	*current);
int			get_arg_num(t_token *current);
char		*get_path(char *command, char **env);
void		write_pipe_in(t_data *data);
t_token		*write_pipe_out(t_data *data, t_token *current);
int			char_is_in_str(char *str, char c);
int			get_output_num(t_token *current);
int			get_input_num(t_token *current);
int			exec_has_pipe(t_token *current);

//Lexer
int			lexer(char *str, t_data *data);
char		**allocate(char **split, int strnumber);
char		**makestring(char **split, char *str, int *start, int *i);
int			is_delimiter(char c);
int			jump_delimiters(char *str, int *i);
int			jump_redir(char *str, int *i);
int			jump_delimiter_split(char **split, char *str, int *start, int *i);
int			switch_flags(int *flag, int quote, int *keep_quote);
int			handle_quote(char *str, int *i, int *flag, int *keep_quote);
int			is_delimiter(char c);
int			quote_is_unbalanced(int singlequote, int doublequote);
int			recognize_quote(char *str, char c);
int			countstrs(char *str);
char		**create_strings(char **split, char *str);

//executer
int			executer(t_data *data);
int			in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe);
int			file_as_stdin(t_exec *exec);
int			file_as_stdout(t_exec *exec);
int			pipe_as_stdin(int fd_keep_pipe);
int			pipe_as_stdout(int *fd_pipe);
void		close_pipe(int *fd_pipe);
int			heredoc(t_exec *exec, int *fd, int i);
int			write_heredoc(t_exec *exec, int *fd, int i);
void		heredoc_as_in(t_exec *exec, int *fd_pipe, int i);
int			init_heredoc_pipe(t_exec *exec, int *fd);
int			open_infile(t_exec *exec, int *fd, int i);
int			error_codes(int pid);
void		wrong_command(t_exec *exec);
void		handle_sigquit(int sig);
void		signals_child(void);
void		command_not_found(char *s, t_data *data);

//builtins
int			built_in(t_exec *exec, char ***env, t_data *data);
int			built_in_child(t_exec *exec, char ***env, t_data *data);
int			is_specialbuiltin(t_exec *exec);
void		is_only_dollarsign(char **s);
int			is_built_in(char *command);

//pwd
int			ft_pwd(void);

//cd
int			ft_cd(t_exec *exec, char ***env);
void		create_cd_error(char *path);

//exit
int			ft_exit(char **args);
void		exit_no_numeric(char *str);
int			exit_too_many_args(void);
int			is_num(char *str);

//echo
int			ft_echo(t_exec *exec, t_data *data);
void		out_echo_str(char **args, char **env, char *out, int end);
int			option_detect(char **args);
int			is_nnn(char *arg);

//echo utils
int			is_quote(char c);
int			count_rm_quotes(char *str);
void		copy_without_quotes(char *out, char *str);
char		*quote_cutter(char *str);

//unset
int			ft_unset(char **args, char ***env);
int			check_unset(char *str);
void		write_unset_err_message(char *str);

//export
int			ft_export(char **args, char ***env);
int			process_export_args(char **args, int i, char ***env);
int			update_env(char *category, char *value, char ***env);

//export_utils
void		export_dclr_message(char **env);
int			check_export(char *str, char *value);
void		write_export_err_message(char *str, char *value);

//env
int			ft_env(char **env);
char		**add_to_env(char *str, char **env);
char		**remove_from_env(char *category, char **env);
char		**replace_in_env(char *category, char *new_entry, char **env);
int			category_is_in_env(char *category, char **env);

//expander
t_exec		**expander(t_exec **exec, char **env, t_data *data);
char		*take_content(char *declaration);
char		*search_var_in_env(char *var, char **env);
void		search_array(char **arr, char **env);
char		*look_for_dollar(char *str, char **env);
char		**if_split_contains_sentence(const char *dollar);
char		*take_var(char *s, char **env);
char		*ft_replace_var(char **env, char *dollar);
char		*string_split(char *str, char c, int at_first, int first);
char		*minimize_whitespace(char *str);
t_exec		*expand(t_exec *exec, char **env);
t_exec		*go_through_exec(t_exec *exec, char **env, t_data *data);
int			look_for_singlequote(char *str, int *flag);
char		**replace_args(char **c_args, char **args, int exp_cycle);
char		**mini_lexer(char *str);
char		**join_2d_array(char **s1, char **s2);
int			var_in_str(char *str);
int			keep_dollar(char *str);
int			ft_length_dollar(char *s, char c);
char		*replace_string(char *s, char **env);
char		*rplc_fnlstring(char *finalstring,
				char *substr, char **env, int flag);

#endif
