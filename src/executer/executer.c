#include "../../include/minishell.h"

int	create_child(t_exec *exec, t_data *data, int *fd_pipe, int fd_keep_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signals_child();
		if (in_out(exec, fd_pipe, fd_keep_pipe) == -1)
			exit (1);
		close_pipe(fd_pipe);
		wrong_command(exec);
		built_in_child(exec, &data->env, data);
		if (execve(exec->command, exec->args, data->env) == -1)
			command_not_found(exec->command, data);
	}
	if (close(fd_pipe[1]) == -1)
		perror ("close pipe[1]");
	if (fd_keep_pipe != 99 && close(fd_keep_pipe) == -1)
		perror ("close keep_pipe");
	return (fd_pipe[0]);
}

void	execute(t_data *data)
{
	int		i;
	int		fd_pipe[2];
	int		fd_keep_pipe;
	int		pid;

	i = 0;
	pid = 0;
	fd_keep_pipe = 99;
	while (data->execs[i])
	{
		if (pipe(fd_pipe) == -1)
			perror("create pipe");
		fd_keep_pipe = create_child(data->execs[i],
				data, fd_pipe, fd_keep_pipe);
		i++;
	}
	if (close(fd_keep_pipe) == -1)
		perror ("close keep_pipe");
	while (i >= 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(0, &pid, 0);
		i--;
	}
	error_codes(pid);
}

int	executer(t_data *data)
{
	if (!data->execs[1] && is_specialbuiltin(data->execs[0]))
		built_in(data->execs[0], &data->env, data);
	else
		execute(data);
	return (0);
}
