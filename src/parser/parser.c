#include "../../include/minishell.h"

void init_exec(t_data *data, t_token *current)
{
	data->execs[data->exec_count] = ft_calloc(sizeof(t_exec) + 1, 1);
	data->execs[data->exec_count]->command = NULL;
	data->execs[data->exec_count]->args = (char **) ft_calloc(sizeof(char *), get_arg_num(current) + 1);
	data->execs[data->exec_count]->input = (char **) ft_calloc((sizeof(char *) * 2) + 1, 1);
	data->execs[data->exec_count]->output = (char **) ft_calloc((sizeof(char *) * 2) + 1, 1);
}

t_token	*write_redirection(t_data *data, t_token *current)
{
	int	j;

	j = 0;
	if(current->content[0] == '<')
	{
		while(j < 2)
		{
			data->execs[data->exec_count]->input[j] = ft_strdup(current->content);
			current = current->next;
			j++;
		}
	}
	else
	{
		while(j < 2)
		{
			data->execs[data->exec_count]->output[j] = ft_strdup(current->content);
			current = current->next;
			j++;
		}
	}
	return (current);
}

t_token	*write_args(t_data *data, t_token *current)
{
	data->execs[data->exec_count]->args[data->arg_count] = ft_strdup(current->content);
	data->arg_count++;
	current = current->next;
	return(current);
}

void get_command(t_data *data)
{
	if (is_built_in(data->execs[data->exec_count]->args[0]))
		data->execs[data->exec_count]->command = ft_strdup(data->execs[data->exec_count]->args[0]);
	else
	{
		data->execs[data->exec_count]->command = get_path(data->execs[data->exec_count]->args[0]);
		if(!data->execs[data->exec_count]->command)
			data->execs[data->exec_count]->command = ft_strdup(data->execs[data->exec_count]->args[0]);
	}

}

int parse_tokens(t_data *data)
{
	t_token *current;

	if(data->tokens)
		current = data->tokens;
	data->execs = ft_calloc(sizeof(t_exec *), get_exec_count(data->tokens) + 1);
	if (!data->execs)
		return(0);
	while (current)
	{
		init_exec(data, current);
		if(data->pipeflag)
			write_pipe_in(data);
		while (current && current->type != is_pipe)
		{
			if (current->type == redirection)
				current = write_redirection(data, current);
			else if (current && (current->type == word || current->type == option))
				current = write_args(data, current);
		}
		get_command(data);
		if (current && current->type == is_pipe)
			current = write_pipe_out(data, current);
	}
	free_tokens(data);
	return(1);
}
