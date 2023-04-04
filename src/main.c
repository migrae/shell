#include "../include/minishell.h"

void	put_new_promptline(void)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	take_input(char **input, char *promptline)
{
	if (isatty(0))
		*input = readline(promptline);
	else
		*input = get_next_line(0);
	if (!*input)
		return (0);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (1);
}

void print_tokens (t_token **token)
{
	t_token *current;
	current = *token;
	while (current)
	{
		ft_printf("Token-Content: %s\n", current->content);
		ft_printf("Token-Type: %d\n", current->type);
		ft_printf("\n", current->type);
		current = current->next;
	}
}

void print_execs(t_data *data)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(data->execs[i])
	{
		ft_printf("EXEC #%i\n", i);
		ft_printf("-------------------\n");
		while(data->execs[i]->input[j])
		{
			ft_printf("INPUT %i: %s\n", j, data->execs[i]->input[j]);
			j++;
		}
		ft_printf("-------------------\n");
		ft_printf("COMMAND:\n");
		ft_printf("%s\n", data->execs[i]->command);
		ft_printf("ARGS:\n");
		j = 0;
		while(data->execs[i]->args[j])
		{
			ft_printf("ARG #%i: %s\n", j, data->execs[i]->args[j]);
			j++;
		}
		ft_printf("-------------------\n");
		j = 0;
		while(data->execs[i]->output[j])
		{
			ft_printf("OUTPUT %i: %s\n", j, data->execs[i]->output[j]);
			j++;
		}
		ft_printf("\n");
		ft_printf("\n");
		j = 0;
		i++;
	}
}

int	g_errno = 0;

int	main(int args, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	data = init_data(env, args, argv);
	while (1)
	{
		signals();
		reset_data(data);
		if (!take_input(&input, data->promptline))
			break ;
		if (ft_strncmp(input, "", 1) == 0)
			continue ;
		if (!lexer(input, data))
			continue ;
		//print_tokens(&data->tokens);
		if (!parse_tokens(data))
			continue ;
		//print_execs(data);
		if (!expander(data->execs, data->env, data))
			continue ;
		//print_execs(data);
		executer(data);
		free_exec(data, input);
		//system("leaks minishell");
	}
	free_data(data);
	//system("leaks minishell");
	return (g_errno);
}
