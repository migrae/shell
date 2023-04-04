#include "../include/minishell.h"

void	free_tokens(t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	if (data->tokens)
	{
		current = data->tokens;
		while (current)
		{
			tmp = current->next;
			free(current->content);
			current->content = NULL;
			free(current);
			current = tmp;
		}
		current = NULL;
	}
}

void	free_exec(t_data *data, char *input)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (data->execs[i])
	{
		if (data->execs[i]->command)
			free(data->execs[i]->command);
		if (data->execs[i]->args)
		{
			/* ft_put2dstr_fd(data->execs[i]->args, 1);
			while(data->execs[i]->args[j])
			{
				ft_printf("FREEING ARG %i : %s\n", j, data->execs[i]->args[j]);
				free(data->execs[i]->args[j]);
				j++;
			}
			ft_printf("FREEING 2D POINTER:\n");
			free(data->execs[i]->args); */
			ft_free2d(data->execs[i]->args);
		}
		if (data->execs[i]->input)
			ft_free2d(data->execs[i]->input);
		if (data->execs[i]->output)
			ft_free2d(data->execs[i]->output);
		if((data->execs[i]))
			free(data->execs[i]);
		data->execs[i] = NULL;
		i++;
	}
	if(data->execs)
	{
		free(data->execs);
		data->execs = NULL;
	}
	if (input)
		free(input);
}

void	free_data(t_data *data)
{
	if (data->execs)
		free_exec(data, NULL);
	if (data->env)
		ft_free2d(data->env);
	if(data->promptline)
		free(data->promptline);
	if (data)
		free(data);
}

t_data	*init_data(char **env, int args, char **argv)
{
	t_data	*data;

	(void)args;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (free(data->promptline), exit(EXIT_FAILURE), NULL);
	//data->execs = NULL;
	//data->tokens = NULL;
	data->promptline = prompt(data);
	data->env = dupclicate_2d(env);
	return (data);
}

void	reset_data(t_data *data)
{
	free(data->promptline);
	data->promptline = prompt(data);
	data->tokens = NULL;
	data->execs = NULL;
	data->pipeflag = 0;
	data->arg_count = 0;
	data->exec_count = 0;
}
