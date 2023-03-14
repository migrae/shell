#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	take_input(char **input, char *promptline)
{
	*input = readline(promptline);
	if (!*input)
		return (ft_putendl_fd("Shell Aborted", 2), 0);
	return (1);
}

int main (int args, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
	args = 0;
	argv = NULL;
	data = ft_calloc(sizeof(t_data), 1);
	if(!data)
		return (free(data->promptline), exit(EXIT_FAILURE), 1);
	init_data(data, env);
	while (1)
	{
		reset_data(data, args, argv);
		if (!take_input(&input, data->promptline))
			return (free_data(data), system("leaks shell"), EXIT_SUCCESS);
		if (ft_strlen(input) > 0)
			add_history(input);
		if (!load_tokens(lexer(input), data))
			return (free_data(data), EXIT_FAILURE);
		print_tokens(&data->tokens);
		if (!parse_tokens(data))
			return (free_data(data), EXIT_FAILURE);
		expander(data->execs, data->env);
		executer(data);
		free_exec(data);
	}
	free_data(data);
	return (0);
}