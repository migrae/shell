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

/* Data contains all the data of one input. This input is divided by prompts
(one prompt could be piped into another). Every Prompt is divided into tokens.
Every token has a tokentype */

int	global = 0;

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

typedef struct s_env
{
	char	**env;
}	t_env;

char		*prompt(t_data *data);
int			load_tokens(char **split_tokens, t_data *data);
t_tokentype	content_analyse(t_token *token);
int 		parse_tokens(t_data *data);

//Utils
int			is_char(char place, char c);
void		freestrings(char *s1, char *s2, char *s3, char **array);
void		printtokens(t_exec **exec);
char		*username(void);
void		print_tokens(t_token **token);
void		free_tokens(t_data *data);
void		free_data(t_data *data);
void		init_data(t_data *data, char **env);
void		reset_data(t_data *data);
void		free_exec(t_data *data);
char		**dupclicate_2D(char **str);
int			ft_2darraylen(char **array);
char		*ft_strjoin_free_opt(char *s1, char *s2, int free_s1, int free_s2);
char		*ft_strjoin_s_e(char **args, int start, int end, char* c);


//Parser
void		init_exec(t_data *data, t_token *current);
t_token		*write_redirection(t_data *data, t_token *current);

//Utils Parser
void		print_execs(t_data *data);
int			get_exec_count(t_token	*current);
int			get_arg_num(t_token *current);
char		*get_path(char *command);
void		write_pipe_in(t_data *data);
t_token		*write_pipe_out(t_data *data, t_token *current);
int			char_is_in_str(char *str, char c);

//Lexer
char		**lexer(char *str);
char		**allocate(char **split, int strnumber);
char		**makestring(char **split, char *str, int start, int i);
int			is_delimiter(char c);
int			jump_delimiters(char *str, int *i);
int			jump_redir(char *str, int *i);
int			jump_delimiter_split(char **split, char *str, int *start, int *i);
void		switch_flags(int *flag, int quote, int *keep_quote);
int			handle_quote(char *str, int *i, int *flag, int *keep_quote);
int			is_delimiter(char c);
char 		**makestring(char **split, char *str, int start, int i);
int 		jump_delimiters(char *str, int *i);
int			jump_redir(char *str, int *i);

//executer
int			executer(t_data *data);
int			in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe);
int			file_as_stdin(t_exec *exec);
int			file_as_stdout(t_exec *exec);
int			pipe_as_stdin(int fd_keep_pipe);
int			pipe_as_stdout(int *fd_pipe);
void		close_pipe(int *fd_pipe);
int			built_in(t_exec *exec, char **env, t_data *data);
int			is_built_in(char *command);
int			is_childless_built_in(char *command);
int			heredoc(t_exec *exec);
t_exec		**expander(t_exec **exec, char **env);

//builtins
int			built_in(t_exec *exec, char **env, t_data *data);
void		ft_echo(t_exec *exec);
char		**ft_export(char **args, char **env);
char		**ft_unset(char **args, char **env);
void		ft_cd(t_exec *exec, char **env);
void		ft_pwd();

//env
void		ft_env(char **env);
int			category_is_in_env(char *category, char **env);
char		**add_to_env(char *str, char **env);
char		**remove_from_env(char *category, char **env);
char		**replace_in_env(char *category, char *new_entry, char **env);

//expander
char		*take_content(char *declaration);
char		*search_var_in_env(char *var, char **env);
void		search_array(char **arr, char **env);
char		*look_for_dollar(char *str, char **env);
char		**if_split_contains_sentence(const char *dollar);
char		*take_var(char *s, char **env);
char		*ft_replace_var(char **env, char *dollar);
char		*search_var_in_env(char *var, char **env);
char		*string_split(char *str, char c, int at_first, int first);
char		*minimize_whitespace(char *str);

#endif
