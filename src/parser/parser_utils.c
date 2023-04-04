#include "../../include/minishell.h"

t_token	*write_args(t_data *data, t_token *current)
{
	if (current->content)
		data->execs[data->exec_count]->args[data->arg_count]
			= ft_strdup(current->content);
	data->arg_count++;
	current = current->next;
	return (current);
}

void	get_command(t_data *data)
{
	int	i;

	i = 0;
	if (!data->execs[data->exec_count]->args[0])
		data->execs[data->exec_count]->command = NULL;
	else
	{
		if(data->execs[data->exec_count]->args[0][0] != '$')
		{
			while (data->execs[data->exec_count]->args[0][i])
			{
					data->execs[data->exec_count]->args[0][i]
						= ft_tolower(data->execs[data->exec_count]->args[0][i]);
				i++;
			}
		}
		data->execs[data->exec_count]->command
			= ft_strdup(data->execs[data->exec_count]->args[0]);
	}
}

t_token	*write_output(t_data *data, t_token *current)
{
	int	j;

	j = data->execs[data->exec_count]->output_written;
	while (current && j < (data->execs[data->exec_count]
			->output_written + 2))
	{
		if (!current)
			exit(2);
		data->execs[data->exec_count]->output[j] = ft_strdup(current->content);
		current = current->next;
		j++;
	}
	data->execs[data->exec_count]->output_written += 2;
	return (current);
}

t_token	*write_input(t_data *data, t_token *current)
{
	int	j;

	j = data->execs[data->exec_count]->input_written;
	while (current && j < (data->execs[data->exec_count]
			->input_written + 2))
	{
		if (!current)
			exit(2);
		data->execs[data->exec_count]->input[j] = ft_strdup(current->content);
		current = current->next;
		j++;
	}
	data->execs[data->exec_count]->input_written += 2;
	return (current);
}

t_token	*write_redirection(t_data *data, t_token *current)
{
	if (current->content[0] == '<')
		current = write_input(data, current);
	else
		current = write_output(data, current);
	return (current);
}
