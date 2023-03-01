#include "../include/minishell.h"

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
		ft_printf("INPUT-TYPE: %s\n", data->execs[i]->input[0]);
		ft_printf("INPUT-SOURCE: %s\n", data->execs[i]->input[1]);
		ft_printf("-------------------\n");
		ft_printf("COMMAND:\n");
		ft_printf("%s\n", data->execs[i]->args[0]);
		ft_printf("ARGS:\n");
		while(data->execs[i]->args[j])
		{
			ft_printf("ARG #%i: %s\n", i, data->execs[i]->args[j]);
			j++;
		}
		ft_printf("-------------------\n");
		ft_printf("OUTPUT-TYPE: %s\n", data->execs[i]->output[0]);
		if(data->execs[i]->output[1])
			ft_printf("OUTPUT-SOURCE: %s\n", data->execs[i]->output[1]);
		ft_printf("\n");
		ft_printf("\n");
		j = 0;
		i++;
	}
}

int	get_exec_count(t_token	*current)
{
	t_token *tmp;
	int		exec_count;

	exec_count = 1;
	tmp = current;
	while (current)
	{
		if (current->type == is_pipe)
			exec_count++;
		current = current->next;
	}
	return (exec_count);
}

int	get_arg_num(t_token *current)
{
	t_token	*tmp;
	int		arg_count;

	arg_count = 0;
	tmp = current;
	while (tmp && tmp->type != is_pipe)
	{
		if(tmp->type == redirection)
			tmp = tmp->next->next;
		else
		{
			arg_count++;
			tmp = tmp->next;
		}
			
	}
	return(arg_count);
}